#pragma once
#include "pch.h"
#include "State.h"
#include "IPipeManager.h"

class Game : public State
{
public:
	Game(bool online);
	~Game();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

private:
	//draw
	void drawUI();

	IPipeManager* pipeManager;
	std::wstring str;

};

