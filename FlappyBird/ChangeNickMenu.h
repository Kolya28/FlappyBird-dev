#pragma once
#include "State.h"

class ChangeNickMenu :
	public State
{
public:
	ChangeNickMenu(float *scale)
		:scale(scale){}

	~ChangeNickMenu() {};

	void init() override;
	void cleanup() override {};

	void handleEvent(sf::Event& ev) override;
	void update(float dt) override {}
	void draw() override { engine->window.draw(text); }

private:
	void rescale();

	sf::Font font;
	sf::Text text;
	std::string nick;
	
	float* scale = nullptr;
	sf::Vector2f nick_pos = sf::Vector2f(0.5f, 0.5f);
	
};

