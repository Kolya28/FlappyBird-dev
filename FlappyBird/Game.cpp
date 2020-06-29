#include "pch.h"
#include "Game.h"

Game::Game(bool online)
{
	if (online)
	{
		pipeManager = new PipeManagerMultiPlayer;
	}
	else
	{
		pipeManager = new PipeManagerSinglePlayer;
	}



}

Game::~Game()
{
}

void Game::init()
{
}

void Game::cleanup()
{
}

void Game::handleEvent(sf::Event& ev)
{
	switch (ev.type)
	{
	
	}
}

void Game::update(float dt)
{
}

void Game::draw()
{
	drawUI();
}

void Game::drawUI()
{
}
