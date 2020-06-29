#pragma once
#include "State.h"
#include "Game.h"

class ConnectState :
	public State
{
public:
	ConnectState();
	~ConnectState();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

private:
};

