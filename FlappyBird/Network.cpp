#include "pch.h"
#include "Network.h"

struct in_addr Network::GetIpFromHostname(const char *str)
{
	auto ip = gethostbyname(str);
	if (ip == nullptr)
	{
		struct in_addr t;
		t.s_addr = INADDR_NONE;
		return t;
	}

	return *(struct in_addr*)ip->h_addr_list[0];
}
void Network::startup()
{
	if (!started)
	{
		wsVersion = MAKEWORD(2, 2);

		if (WSAStartup(wsVersion, &wsaData) != 0)
			throw std::exception("WSAStartup failed with error");

		


		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
			throw std::exception("Could not find a usable version of Winsock.dll");

		started = true;
	}
}

void Network::cleanup()
{
	if (started)
	{
		if (WSACleanup() == SOCKET_ERROR)
			throw std::exception("WSACleanup failed with error");

		started = false;
	}
}

SOCKET Network::tcpconnect(std::string hostname, unsigned short port)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	
	addr.sin_addr = GetIpFromHostname(hostname.c_str());
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (connect(s, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
		return SOCKET_ERROR;
	else
		return s;
}


bool Network::connectUdp()
{
	udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (udp == INVALID_SOCKET)
		return false;

	std::string get_token("GET_TOKEN_");
	get_token += VERSION;

	if (connect(udp, (SOCKADDR*)&server_addr_udp, sizeof(server_addr_udp)) != 0)
		return false;

	send(udp, get_token.c_str(), get_token.size() + 1, NULL);//, (SOCKADDR*)&server_addr, sizeof(server_addr));

	if (waitData(udp, 2l) <= 0)
		return false;

	char buff[BUFFSIZE+1];
	buff[BUFFSIZE] = '\0';

	int size = recv(udp, buff, BUFFSIZE, NULL);

	if (size == SOCKET_ERROR)
		return false;

	std::cout << "token " << buff << std::endl;

	token = buff;

	return true;
}

bool Network::connectTcp()
{
	tcp = socket(AF_INET, SOCK_STREAM, NULL);
	if (tcp == INVALID_SOCKET)
		return false;

	if (connect(tcp, (SOCKADDR*)&server_addr_tcp,
		sizeof(server_addr_tcp)) != 0)
		return false;

	std::string version("Version_");
	version += VERSION;

	if (send(tcp, version.c_str(), version.size() + 1, NULL) < 1)
		return false;

	Sleep(100);
	
	if (send(tcp, token.c_str(), token.size() + 1, NULL) < 1)
		return false;

	if (waitData(tcp, 1) <= 0)
		return false;

	char buff[BUFFSIZE];

	int size = recv(tcp, buff, BUFFSIZE, NULL);

	if (size == SOCKET_ERROR)
		return false;

	return size == 3 && buff[0] == 'O' && buff[1] == 'K';
}

int Network::waitData(SOCKET s, long seconds)
{
	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set); /* clear the set */
	FD_SET(s, &set); /* add our file descriptor to the set */
	timeout.tv_sec = seconds;
	timeout.tv_usec = 0;

	return select(NULL, &set, NULL, NULL, &timeout);
}

bool Network::connectToServer()
{
	struct in_addr server_ip;
	server_ip.s_addr = 0;

	for (auto& h : config.hostnames)
	{
		auto ip = GetIpFromHostname(h.c_str());
		
		if (ip.s_addr != INADDR_NONE)
		{
			server_ip = ip;
			break;
		}
	}
	
	server_ip.s_addr = inet_addr("192.168.88.254");

	if (server_ip.s_addr == 0)
		return false;

	server_addr_udp.sin_family = AF_INET;
	server_addr_udp.sin_addr = server_ip;
	server_addr_udp.sin_port = htons(config.udp_port);

	server_addr_tcp.sin_family = AF_INET;
	server_addr_tcp.sin_port = htons(config.tcp_port);
	server_addr_tcp.sin_addr = server_ip;

	if (connectUdp())
		if (connectTcp())
			return true;
	
	//if (tcp != INVALID_SOCKET)
		closesocket(tcp);

	//if (udp != INVALID_SOCKET)
		closesocket(udp);
	

	return false;
}


Network::Network()
{
	
}

Network::~Network()
{
	cleanup();
}


