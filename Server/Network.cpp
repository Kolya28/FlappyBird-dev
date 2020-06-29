#include "pch.h"
#include "Network.h"

struct in_addr Network::GetMyIp()
{
	struct in_addr ip;
	inet_pton(AF_INET, "192.168.1.34", &ip);
	return ip;
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

	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = INADDR_ANY;
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


SOCKET Network::listenSocket(SOCKET s, u_short port)
{
	if (s < 0)
	{
		throw std::exception(("failed socket " +
			std::to_string(WSAGetLastError())).c_str());
	}

	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = INADDR_ANY;
	hint.sin_port = htons(port);

	if (bind(s, (SOCKADDR*)&hint, sizeof(hint)))
	{
		closesocket(s);
		throw std::exception(("failed bind " + 
			std::to_string(WSAGetLastError())).c_str());
	}

	if (listen(s, SOMAXCONN))
	{
		//closesocket(s);
		//throw std::exception(("failed listen " +
		//	std::to_string(WSAGetLastError())).c_str());
	}

	return s;
}


Network::Network()
{
	
}

Network::~Network()
{
	cleanup();
}


