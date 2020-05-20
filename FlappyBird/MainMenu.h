#pragma once
#include "pch.h"

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<cmath>
#include<functional>
#include<iostream>

#include "State.h"

class Button
{
public:
	Button(std::string str, std::function<bool()> onPressed)
	{
		this->str = str;
		this->onPressed = onPressed;
	}

	std::string str;
	std::function<bool()> onPressed;
};

class MainMenu : public State
{
public:
	MainMenu();
	~MainMenu();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

	void pause() override;
	void resume() override;

private:
	void rescale();
	void placeButtons();

	//global
	float scale;

	//button
	sf::Vector2f grid_centre;
	sf::Vector2f grid_pos;
	sf::Vector2f grid_begin;
	float spacing;
	int n = 0;
	std::string menu_dir;
	std::vector<Button> button;
	sf::Font font;
	sf::Text text;
	sf::Color c_buttonP, c_buttonR, c_buttonA;
	sf::Texture t_buttonP, t_buttonR, t_buttonA;
	sf::Sprite s_button;

	//mouse
	bool enableMouse = true;
	bool pressed = false;
	bool mouseHover = false;
	sf::Vector2f mouse_pos;

	//cursor
	int pos = 0;
	int active_pos = 0;
};

