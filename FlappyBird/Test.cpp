#include "pch.h"
#include "Test.h"

Test::Test()
{
}

Test::~Test()
{
}

void Test::init()
{
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(50.f);
	circle.setPosition(500.f/2,500.f/2);

	sr.setFillColor(sf::Color::Red);
	sr.setSize(static_cast<sf::Vector2f>(engine->window.getSize()));
	bloom.loadFromFile("Shaders\\bloom.frag", sf::Shader::Type::Fragment);
	//bloom.setUniform("max_dist", (float)std::max(engine->window.getSize().x,
		//engine->window.getSize().y)/4.f*3.f);

	bloom.setUniform("u_resolution", sf::Glsl::Vec2(engine->window.getSize()));

	time = 0;
}

void Test::cleanup()
{
}

void Test::handleEvent(sf::Event& ev)
{
	if(ev.type == sf::Event::KeyPressed &&
		ev.key.code == sf::Keyboard::Escape)
		engine->popState();
}

void Test::update(float dt)
{
	time += dt*5.f;
}

void Test::draw()
{
	//bloom.setUniform("t0", sf::Shader::CurrentTexture);

	auto pos = sf::Mouse::getPosition(engine->window);
	pos.y = engine->window.getSize().y - pos.y;

	//bloom.setUniform("u_mouse", sf::Glsl::Vec2(pos));
	bloom.setUniform("u_time", time);
	engine->window.draw(sr, &bloom);
}

void Test::pause()
{
}

void Test::resume()
{
}
