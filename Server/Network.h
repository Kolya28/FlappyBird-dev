#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
	int waitData(SOCKET s, long seconds);
	SOCKET listenSocket(SOCKET s, u_short port);
	void startup();
	void cleanup();

	Network();
	~Network();

	
	NetworkConfig config;
	SOCKADDR_IN hint;
private:
	//int searchlocal();
	//int search();
	bool started = false;
	
	WORD wsVersion;
	WSAData wsaData;

	struct in_addr GetMyIp();


	
};
