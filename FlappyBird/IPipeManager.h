#pragma once
#include "pch.h"
#include <deque>
#include <functional>
#include <algorithm>

class Pipe
{
public:

	Pipe(float pHeight, float pPos) :
		height(pHeight), pos(pPos)
	{}

	void draw(sf::RenderTarget& target)
	{
		float h = target.getView().getSize().y;

		pipe_bottom->setPosition(pos, h - height * *scale);
		pipe_top->setPosition(pos, h - (height + space) * *scale);

		target.draw(*pipe_bottom);
		target.draw(*pipe_top);
	}

	float height, pos;
	static sf::Sprite* pipe, * pipe_top, * pipe_bottom;
	static float space;
	static float* scale;
};


class IPipeManager
{
public:
	IPipeManager();
	~IPipeManager();

	void loadTextures();
	void rescale();

	void init(float width, float space, float* scale);


	void setPipeWidth(float width) { pipe_width = width; };
	virtual void addPipe(float height, float pos) = 0;
	void popFront() { pipes.pop_front(); };


	bool checkCollision(sf::CircleShape player_hitbox);

	void drawPipes(float relativeTo, sf::RenderTarget& target);

private:
	float* scale = nullptr;
	float pipe_width = 0;
	std::deque<Pipe> pipes;
	std::function<bool(const Pipe& a, const Pipe& b)> pipe_pred = [](const Pipe& a, const Pipe& b)
	{
		return a.pos < b.pos;
	};
};

class PipeManagerSinglePlayer : public IPipeManager
{
public:
	void addPipe(float pos, float height) override
	{

	}
};

class PipeManagerMultiPlayer : public IPipeManager
{
public:
	void addPipe(float pos, float height) override
	{

	}
};

