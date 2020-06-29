#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define BUFFSIZE 1024
#include "pch.h"

#pragma comment(lib,"ws2_32.lib")
#include <ws2tcpip.h>
#include <Windows.h>
#include <iostream>
#include <string>


#include "NetworkConfig.h"

class Network
{
public:
	SOCKET tcpconnect(std::string hostname, unsigned short port);

	bool connectToServer();

	void startup();
	void cleanup();

	Network();
	~Network();
	
	NetworkConfig config;

private:
	bool connectUdp();
	bool connectTcp();

	int waitData(SOCKET s, long seconds);
	
	//int searchlocal();
	//int search();

	bool started = false;

	WORD wsVersion;
	WSAData wsaData;

	SOCKADDR_IN server_addr_tcp, server_addr_udp;
	std::string token;
	SOCKET tcp, udp;
	
	struct in_addr GetIpFromHostname(const char* str);
};
