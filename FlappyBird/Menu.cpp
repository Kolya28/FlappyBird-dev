#include "pch.h"
#include "Menu.h"

Menu::Menu()
{
	
}

Menu::~Menu()
{
}

void Menu::init()
{
	dir = engine->assetsDir / "States" / "Menu";

	c_buttonA = c_buttonP = c_buttonR = sf::Color::Color(200, 200, 200, 255);
	text.setFont(
		engine->assets.load<sf::Font>("menu/font", dir / "font.ttf")
		);

	assets->load<sf::Texture>("menu/button_active", dir/"button_hover.png");
	assets->load<sf::Texture>("menu/button_pressed", dir / "button_pressed.png");
	assets->load<sf::Texture>("menu/button_released", dir / "button_released.png");
	/*t_buttonA.loadFromFile(dir + "\\button_hover.png");
	t_buttonP.loadFromFile(dir + "\\button_pressed.png");
	t_buttonR.loadFromFile(dir + "\\button_released.png");*/
	
	s_button.setTexture(
		assets->get<sf::Texture>("menu/button_released")
			);

	spacing = 20.f;
	grid_centre = sf::Vector2f(0.5f, 0.5f);


	placeButtons();
	n = buttons.size();

	rescale();
}

void Menu::cleanup()
{
	assets->clean("menu/font");
	assets->clean("menu/button_active");
	assets->clean("menu/button_pressed");
	assets->clean("menu/button_released");
}

void Menu::rescale()
{
	sf::Vector2f view = static_cast<sf::Vector2f>(engine->window.getSize());
	
	float SizeY = s_button.getTexture()->getSize().y * n
		+ spacing * (n - 1);

	if (engine->getScale() != 0)
		scale = engine->getScale();
	else
	{
		scale = std::min(std::round(view.y / (SizeY + 200.f)),
			std::round(view.x / (s_button.getTexture()->getSize().x + 100.f)));

		if (scale == 0.f)
			scale = 1.f;
	}

	s_button.setScale(scale, scale);
	text.setCharacterSize(10*scale);

	grid_pos = sf::Vector2f(std::round(view.x * grid_centre.x),
		std::round(view.y * grid_centre.y));

	grid_pos.y -= SizeY*scale / 2.f;
	grid_pos.x -= s_button.getGlobalBounds().width / 2.f;
}



void Menu::handleEvent(sf::Event& ev)
{
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		enableMouse = false;
	case sf::Event::MouseButtonPressed:
			switch (ev.key.code)
			{
			case sf::Keyboard::Up:
				if (active_pos == -1)
					active_pos = 0;

				if (active_pos > 0)
					--active_pos;
				break;

			case sf::Keyboard::Down:
				if (active_pos < n - 1)
					++active_pos;
				break;

			case sf::Mouse::Button::Left:
				if (!mouseHover || !enableMouse)
					break;
			case sf::Keyboard::Enter:
				pressed = true;
				break;

			case sf::Keyboard::Escape:
				engine->popState();
				return;
				break;
			}
			break;

	case sf::Event::KeyReleased:
	case sf::Event::MouseButtonReleased:
			switch (ev.key.code)
			{
			case sf::Mouse::Button::Left:
				if (!enableMouse)
					break;
			case sf::Keyboard::Enter:
			
				
				if (pressed && active_pos != -1)
				{
					pressed = false;

					buttons[active_pos].onClick();	
				}
				break;
			}
			break;

	case sf::Event::Resized:
			rescale();
			//std::cout << engine->window.getSize().x << ' ' << engine->window.getSize().y <<std::endl;
			break;

	case sf::Event::MouseMoved:
		mouse_pos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(engine->window));
		enableMouse = true;
		break;
	}

}

void Menu::update(float dt)
{
	if (!enableMouse)
		return;

	mouseHover = false;
	sf::FloatRect box = s_button.getGlobalBounds();
	box.left = grid_pos.x;
	box.top = grid_pos.y;

	for (int i = 0; i < n; ++i)
	{
		if (box.contains(mouse_pos))
		{
			active_pos = i;
			mouseHover = true;
			break;
		}

		box.top += s_button.getGlobalBounds().height + spacing * scale;
	}
}

void Menu::draw()
{
	s_button.setPosition(grid_pos);

	for (int i = 0; i < n; ++i)
	{
		if (i == active_pos)
			if (!pressed)
				s_button.setTexture(assets->get<sf::Texture>("menu/button_active")),
				text.setFillColor(c_buttonA);
			else
				s_button.setTexture(assets->get<sf::Texture>("menu/button_pressed")),
				text.setFillColor(c_buttonP);
		else
			s_button.setTexture(assets->get<sf::Texture>("menu/button_released")),
			text.setFillColor(c_buttonR);


		text.setString(buttons[i].str);

		text.setPosition(s_button.getPosition() +
			sf::Vector2f(s_button.getGlobalBounds().width, s_button.getGlobalBounds().height) / 2.f -
			sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) / 2.f);

		text.setPosition(std::round(text.getPosition().x), std::round(text.getPosition().y));
		
		engine->window.draw(s_button);
		engine->window.draw(text);

		s_button.move(0, s_button.getGlobalBounds().height + spacing * scale);
	}
}