#pragma once
#include "pch.h"

#include<SFML/Graphics.hpp>
#include<iostream>
#include "State.h"
class Test :
	public State
{
public:
	Test();
	~Test();

	void init() override;
	void cleanup() override;

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override;
	void draw() override;

	void pause() override;
	void resume() override;

private:
	sf::Shader bloom;
	sf::CircleShape circle;
	sf::RectangleShape sr;
	float time = 0;
};

