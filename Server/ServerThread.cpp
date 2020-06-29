#include "pch.h"
#include "ServerThread.h"

void ServerThread::init(const fs::path& dir)
{
	try
	{
		ws.startup();
		ws.config.loadFromFile(dir / "network.json");
	}
	catch(std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}

	running = true;
}

void ServerThread::run()
{
	std::thread tcp(&ServerThread::listenTCP, this);
	std::thread udp(&ServerThread::listenUDP, this);

	while (running)
	{
		Sleep(100);
	}

	tcp.join();
	udp.join();
}

void ServerThread::cleanup()
{
	running = false;

	try
	{
		ws.cleanup();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}
}

void ServerThread::listenTCP()
{
	SOCKET s = ws.listenSocket(socket(AF_INET, SOCK_STREAM, NULL), ws.config.tcp_port);
	/*SOCKET s = socket(AF_INET, SOCK_STREAM, NULL);
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(7385);

	bind(s, (SOCKADDR*)&addr, sizeof(addr));
	listen(s, SOMAXCONN);*/

	if (s == INVALID_SOCKET)
	{
		running = false;
		return;
	}


	

	std::string verifly("Version_");
	verifly += VERSION;

	std::cout << "listenTCP\n";

	while (running)
	{
		//if (ws.waitData(s, 1l) <= 0)
		//	continue;

		SOCKADDR_IN addr;
		int sizeofaddr = sizeof(addr);

		SOCKET new_connection = accept(s, (SOCKADDR*)&addr, &sizeofaddr);

		
		std::cout << "tcp " << inet_ntoa(addr.sin_addr) << ':' << ntohs(addr.sin_port) << std::endl;

		std::thread new_tcp([&](SOCKET connection)
			{
				char buff[BUFFSIZE + 1];
				buff[BUFFSIZE] = '\0';

				std::cout << "tcp: connect \n";
				int size = recv(connection, buff, BUFFSIZE, NULL);

				std::cout << "tcp: " << buff << std::endl;

				if (size - 1 != verifly.size() && verifly != buff)
				{
					closesocket(connection);
					return;
				}

				buff[0] = '\0';
				size = recv(connection, buff, BUFFSIZE, NULL);
				std::cout << "tcp: " << buff << std::endl;

				if (size <= 0 || !Connection::checkToken(buff, connection))
					closesocket(connection);
			}, new_connection);
		new_tcp.detach();
	}
}

void ServerThread::listenUDP()
{
	SOCKET s = ws.listenSocket(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP), ws.config.udp_port);
	if (s == INVALID_SOCKET)
		return;


	Connection::udp = s;

	std::string get_token("GET_TOKEN_");
	get_token += VERSION;

	char buff[BUFFSIZE+1];
	buff[BUFFSIZE] = '\0';

	SOCKADDR_IN client_addr;
	int sizeaddr = sizeof(client_addr);

	std::cout << "listenUDP\n";

	while (running)
	{
		ZeroMemory(&client_addr, sizeof(client_addr));

		if (ws.waitData(s, 1l) <= 0)
			continue;

		int size = recvfrom(s, buff, BUFFSIZE, NULL, (SOCKADDR*)&client_addr, &sizeaddr);
		if (size == SOCKET_ERROR)
			return;

		std::cout << "udp " << inet_ntoa(client_addr.sin_addr) << ':' << ntohs(client_addr.sin_port) << std::endl;

		std::cout << "udp: " << buff << std::endl;

		if (get_token.size() == size-1 && get_token == buff)
		{
			auto player_thread = new std::thread([](SOCKET s, SOCKADDR_IN addr)
				{
					Connection* t = new Connection;

					if (!t->sendToken(s, addr))
						return;

					t->waitToken();
					delete t;
				}, s, client_addr);
		}
	}

	running = false;
}