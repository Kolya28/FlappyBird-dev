#include "pch.h"
#include "IPipeManager.h"

float Pipe::space = 0.f;
float* Pipe::scale = nullptr;
sf::Sprite* Pipe::pipe = nullptr;
sf::Sprite* Pipe::pipe_top = nullptr;
sf::Sprite* Pipe::pipe_bottom = nullptr;

IPipeManager::IPipeManager()
{
}

IPipeManager::~IPipeManager()
{
}

void IPipeManager::loadTextures()
{
}

void IPipeManager::rescale()
{
}

void IPipeManager::init(float width, float space, float* scale)
{
	Pipe::scale = scale;
	this->scale = scale;

	pipe_width = width;
}

bool IPipeManager::checkCollision(sf::CircleShape player_hitbox)
{
	float pos = player_hitbox.getPosition().x - pipe_width - player_hitbox.getRadius();

	auto pipe = std::lower_bound(pipes.begin(), pipes.end(),
		Pipe(0, pos), pipe_pred);

	sf::FloatRect pipe_hitbox_top(0.f, -1000000000.f, pipe_width, 0.f);
	sf::FloatRect pipe_hitbox_bottom(0.f, 0.f, pipe_width, 1000000000.f);

	for (auto it = pipe;
		it->pos >= player_hitbox.getPosition().x + player_hitbox.getRadius()
		&& it != pipes.end();
		++it)
	{
		pipe_hitbox_top.left = pipe_hitbox_bottom.left = it->pos;
		pipe_hitbox_bottom.top = it->height;
		pipe_hitbox_top.height = pipe_hitbox_top.top * -1.f - Pipe::space;

		if (pipe_hitbox_top.intersects(player_hitbox.getGlobalBounds()) ||
			pipe_hitbox_bottom.intersects(player_hitbox.getGlobalBounds()))
			return true;
	}

	return false;
}

void IPipeManager::drawPipes(float relativeTo, sf::RenderTarget& target)
{
	auto pipe = std::lower_bound(pipes.begin(), pipes.end(),
		Pipe(0, relativeTo), pipe_pred);

	if (pipe == pipes.end())
		return;

	for (auto it = pipe;
		it->pos <= relativeTo + target.getSize().x && it != pipes.end();
		++it)
	{
		it->draw(target);
	}
}