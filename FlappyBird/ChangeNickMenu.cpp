#include "pch.h"
#include "ChangeNickMenu.h"

void ChangeNickMenu::init()
{
	nick = engine->myPlayer.nick;
	//font.loadFromFile((engine->assetsDir / "States" / "Menu" / "font.ttf").string());

	font = engine->assets.get<sf::Font>("menu/font");

	text.setString(nick);
	text.setFont(font);

	rescale();
}

void ChangeNickMenu::handleEvent(sf::Event& ev)
{

	switch (ev.type)
	{
	case sf::Event::Resized:
		rescale();
		//std::cout << engine->window.getSize().x << ' ' << engine->window.getSize().y <<std::endl;
		break;

	case sf::Event::TextEntered:

		if (ev.text.unicode > 255)
			break;

		if (ev.text.unicode == 8)
		{
			if (!nick.empty())
				nick.pop_back();
		}
		else
		{
			nick.push_back(ev.text.unicode);
		}

		text.setString(nick);
		rescale();
		break;

	case sf::Event::KeyPressed:
		switch (ev.key.code)
		{
		case sf::Keyboard::Enter:
		case sf::Keyboard::Escape:
			engine->myPlayer.nick = nick;
			engine->savePlayer();
			engine->popState();
		}
	}
}

void ChangeNickMenu::rescale()
{
	sf::Vector2f view = static_cast<sf::Vector2f>(engine->window.getSize());

	text.setCharacterSize(15 * *scale);

	sf::Vector2f pos = sf::Vector2f(view.x * nick_pos.x,
		view.y * nick_pos.y);

	pos.x -= text.getGlobalBounds().width / 2.f;
	pos.y -= text.getGlobalBounds().height / 2.f;

	text.setPosition(pos);
}
