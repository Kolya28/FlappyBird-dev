#pragma once
#include "pch.h"

#include "AssetsManager.h"
#include "State.h"
#include "Settings.h"
#include "MyPlayer.h"
#include "Network.h"

class State;

class StatesManager
{
public:
	StatesManager();
	~StatesManager();
	void init(const fs::path& dir, const std::string &title);
	void cleanup();

	void handleEvent(sf::Event &ev);
	void update(float dt);
	void draw();

	void pushState(State *newState);
	void popState();
	void changeState(State* newState);

	void quit();

	bool isRunning() const;

	//settings
	void savePlayer() { myPlayer.saveToFile(dir / "player.json"); }

	float getScale() { return settings.scale; }
	void setScale(float scale) { settings.scale = scale; }

	int getMaxFps() { return settings.max_fps; }


	

	sf::RenderWindow window;
	fs::path dir, assetsDir;

	AssetsManager assets;
	Network ws;
	MyPlayer myPlayer;

private:
	
	
	Settings settings;

	bool running;

	sf::View defaultView;
	std::vector<State*> states;
};

