#pragma once
#include "pch.h"

#include<SFML/Graphics.hpp>
#include <Windows.h>
#include <filesystem>

#include "State.h"
#include <vector>

namespace fs = std::filesystem;
class State;

class StatesManager
{
public:
	void init(std::string dir, int h, int v, const std::string &title, bool fullscreen);
	void cleanup();

	void handleEvent(sf::Event &ev);
	void update(float dt);
	void draw();

	void pushState(State *newState);
	void popState();
	void changeState(State* newState);

	void quit();

	bool isRunning() const;

	float getUserScale() { return userScale; }
	bool isUserScaleChanged() { return userScaleChanged; }
	void setUserScale(float scale);

	sf::RenderWindow window;
	std::string dir;

private:
	bool userScaleChanged = false;
	float userScale = 1.f;
	bool running;
	int h, v; //screen
	sf::View defaultView;
	HWND hwnd;
	HDC  hdc;
	
	std::vector<State*> states;
};

