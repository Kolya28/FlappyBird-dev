#include "pch.h"
#include "ConnectState.h"

ConnectState::ConnectState()
{
}

ConnectState::~ConnectState()
{
}

void ConnectState::init()
{
	
}

void ConnectState::cleanup()
{
}

void ConnectState::handleEvent(sf::Event& ev)
{
}

void ConnectState::update(float dt)
{
	if (engine->ws.connectToServer())
	{
		std::cout << "connected\n";
		engine->changeState(new Game(true));
	}
	else
	{
		std::cout << "can't connect to server\n";
		engine->popState();
	}
}

void ConnectState::draw()
{
}
