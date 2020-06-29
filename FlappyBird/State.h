#pragma once
#include "pch.h"
#include "StatesManager.h"

class StatesManager;

class State
{
	friend StatesManager;
public:
	State() {}
	virtual ~State() {}
	
	virtual void init() = 0;
	virtual void cleanup() = 0;
	
	virtual void handleEvent(sf::Event& ev) = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual void pause()
	{
		isVisible = false;
		isStopped = true;
	}

	virtual void resume()
	{
		isVisible = true;
		isStopped = false;
	}

	bool isVisible = true;
	bool isStopped = false;


protected:
	static StatesManager* engine;
	static AssetsManager* assets;
};

