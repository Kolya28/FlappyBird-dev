#pragma once
#include "pch.h"
#include "State.h"

class Game : public State
{
public:
	Game();
	~Game();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

	void pause() override;
	void resume() override;
private:
};

