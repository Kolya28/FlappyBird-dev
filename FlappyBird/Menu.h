#pragma once
#include "pch.h"

#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<cmath>
#include<functional>
#include<iostream>

#include "Game.h"
#include "State.h"

class Button
{
public:
	Button(std::string str, std::function<void()> onClick)
	{
		this->str = str;
		this->onClick = onClick;
	}

	std::string str;
	std::function<void()> onClick;
};

class Menu : public State
{
public:
	Menu();
	~Menu();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

protected:
	virtual void placeButtons() = 0;
	std::vector<Button> buttons;
	float scale;

private:
	void rescale();
	//scale
	

	//button
	sf::Vector2f grid_centre;
	sf::Vector2f grid_pos;
	sf::Vector2f grid_begin;
	float spacing;
	int n = 0;
	fs::path dir;
	
	sf::Text text;
	sf::Color c_buttonP, c_buttonR, c_buttonA;
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

