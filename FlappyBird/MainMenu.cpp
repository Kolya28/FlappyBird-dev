#include "pch.h"
#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::init()
{
	menu_dir = engine->dir + "\\Assets\\States\\MainMenu\\";

	c_buttonA = c_buttonP = c_buttonR = sf::Color::Color(200, 200, 200, 255);
	font.loadFromFile(menu_dir+"font.ttf");
	text.setFont(font);

	t_buttonA.loadFromFile(menu_dir + "button_hover.png");
	t_buttonP.loadFromFile(menu_dir + "button_pressed.png");
	t_buttonR.loadFromFile(menu_dir + "button_released.png");
	
	s_button.setTexture(t_buttonR);

	

	spacing = 20.f;
	grid_centre = sf::Vector2f(0.5f, 0.5f);


	placeButtons();
	rescale();
}

void MainMenu::placeButtons()
{
	button.emplace_back("Play", [&]() {std::cout << "Play\n"; return false; });
	button.emplace_back("Online", [&]() {std::cout << "Online\n"; return false; });
	button.emplace_back("Settings", [&]() {std::cout << "Settings\n"; return false; });
	button.emplace_back("Exit", [&]() {engine->popState(); return true; });
	n = button.size();
}

void MainMenu::rescale()
{
	sf::Vector2f view = static_cast<sf::Vector2f>(engine->window.getSize());
	
	float SizeY = t_buttonP.getSize().y * n + spacing * (n - 1);

	scale = std::min(std::round(view.y / (SizeY + 200.f / engine->getUserScale())),
		std::round(view.x / (t_buttonA.getSize().x + 100.f / engine->getUserScale())));
	
	if (scale == 0.f)
		scale = 1.f;

	s_button.setScale(scale, scale);
	text.setCharacterSize(10*scale);

	grid_pos = sf::Vector2f(std::round(view.x * grid_centre.x),
		std::round(view.y * grid_centre.y));

	grid_pos.y -= SizeY*scale / 2.f;
	grid_pos.x -= s_button.getGlobalBounds().width / 2.f;

	/*std::cout << engine->window.getSize().x << 'x'
		<< engine->window.getSize().y << std::endl
		<< grid_pos.x << 'x' << grid_pos.y << "\n\n";*/
}

void MainMenu::cleanup()
{
}

void MainMenu::handleEvent(sf::Event& ev)
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
					if (button[active_pos].onPressed())
						return;
					pressed = false;
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

void MainMenu::update(float dt)
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

void MainMenu::draw()
{
	s_button.setPosition(grid_pos);

	for (int i = 0; i < n; ++i)
	{
		if (i == active_pos)
			if (!pressed)
				s_button.setTexture(t_buttonA),
				text.setFillColor(c_buttonA);
			else
				s_button.setTexture(t_buttonP),
				text.setFillColor(c_buttonP);
		else
			s_button.setTexture(t_buttonR),
			text.setFillColor(c_buttonR);


		text.setString(button[i].str);

		text.setPosition(s_button.getPosition() +
			sf::Vector2f(s_button.getGlobalBounds().width, s_button.getGlobalBounds().height) / 2.f -
			sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height) / 2.f);

		text.setPosition(std::round(text.getPosition().x), std::round(text.getPosition().y));
		
		engine->window.draw(s_button);
		engine->window.draw(text);

		s_button.move(0, s_button.getGlobalBounds().height + spacing * scale);
	}
}

void MainMenu::pause()
{
}

void MainMenu::resume()
{
}


