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

	}

	float height, pos;
	static sf::Sprite* pipe, pipe_top, pipe_bottom;
};

class IPipeManager
{
public:
	void setPipeWidth(float width) { pipe_width = width; };
	virtual void addPipe(float height, float pos) = 0;
	void popFront() { pipes.pop_front(); };


	void checkCollision(sf::CircleShape player_hitbox)
	{
		float pos = player_hitbox.getPosition().x - pipe_width - player_hitbox.getRadius();

		auto pipe = std::lower_bound(pipes.begin(), pipes.end(),
			Pipe(0, pos), pipe_pred);

		sf::FloatRect pipe_hitbox_top(0.f,-1000000000.f, pipe_width, 0.f);
		sf::FloatRect pipe_hitbox_bottom(0.f, 0.f, pipe_width, 1000000000.f);

		for (auto it = pipe;
			it->pos >= player_hitbox.getPosition().x + player_hitbox.getRadius()
			&& it != pipes.end();
			++it)
		{

		}
	}

	void drawPipes(float relativeTo, sf::RenderTarget& target)
	{
		auto pipe = std::lower_bound(pipes.begin(), pipes.end(),
			Pipe(0, relativeTo), pipe_pred);

		if (pipe == pipes.end())
			return;

		for (auto it = pipe;
			it->pos <= relativeTo + target.getSize().x && it!=pipes.end();
			++it)
		{
			it->draw(target);
		}
	}

private:
	float pipe_width = 0;
	std::deque<Pipe> pipes;
	std::function<bool(const Pipe& a, const Pipe& b)> pipe_pred = [](const Pipe& a, const Pipe& b)
	{
		return a.pos < b.pos;
	};
};

