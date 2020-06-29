#pragma once
#include "pch.h"
#include "Network.h"
#include "GameRoom.h"
#include "Connection.h"

#define BUFFSIZE 1024

class ServerThread
{
public:
	void init(const fs::path& dir);
	void run();
	void cleanup();
	
private:

	void listenTCP();
	void listenUDP();

	std::list<GameRoom> rooms;

	std::mutex mtx_players;
	//std::list<Player> players;

	bool running = false;
	Network ws;
};

