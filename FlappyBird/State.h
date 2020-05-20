#pragma once
#include "pch.h"

#include<SFML/Graphics.hpp>
#include "StatesManager.h"

class StatesManager;

class State
{
public:
	void setEngine(StatesManager* engine) { this->engine = engine; };
	virtual void init() = 0;
	virtual void cleanup() = 0;
	
	virtual void handleEvent(sf::Event& ev) = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	bool isVisible = true;
	bool isStopped = false;

	virtual ~State() {};

protected:

	StatesManager* engine;
};

