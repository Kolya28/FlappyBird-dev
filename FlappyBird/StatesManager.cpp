#include "pch.h"
#include "StatesManager.h"

StatesManager::StatesManager()
{
	State::engine = this;
	State::assets = &assets;
}

StatesManager::~StatesManager()
{
}

void StatesManager::init(const fs::path& dir, const std::string& title)
{
	this->dir = dir;
	this->assetsDir = dir / "Assets";
	
	try
	{
		ws.startup();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}


	try
	{
		myPlayer.readFromFile(dir / "player.json");
		settings.loadFromFile(dir / "settings.json");
		ws.config.loadFromFile(dir / "network.json");
	}
	catch(std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}

	window.create(sf::VideoMode(settings.width, settings.height), title,
		(settings.fullscreen ?
			sf::Style::Fullscreen :
			sf::Style::Default));

	window.setVerticalSyncEnabled(settings.vsync);
	window.setKeyRepeatEnabled(settings.key_repeat);

	defaultView = window.getDefaultView();

	running = true;


	auto p = new std::thread([]()
		{
			MSG msg;
			while (GetMessage(&msg, (HWND)NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		});
}

void StatesManager::cleanup()
{
	quit();
	window.close();

	try
	{
		assets.cleanup();
		ws.cleanup();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return;
	}

}

void StatesManager::handleEvent(sf::Event& ev)
{
	if (ev.type == sf::Event::Closed)
	{
		running = false;
		return;
	}

	if (ev.type == sf::Event::Resized)
	{
		defaultView.setCenter(static_cast<sf::Vector2f>(window.getSize()) / 2.f);
		defaultView.setSize(static_cast<sf::Vector2f>(window.getSize()));
		window.setView(defaultView);

		if (settings.scale != 0.f)
			return;
	}

	for (auto& s : states)
		if (!s->isStopped)
			s->handleEvent(ev);
}

void StatesManager::update(float dt)
{
	for (auto& s : states)
		if (!s->isStopped)
			s->update(dt);
}

void StatesManager::draw()
{
	window.clear();

	for (auto& s : states)
		if (s->isVisible)
			s->draw();

	window.display();
}

void StatesManager::pushState(State* newState)
{
	newState->init();
	states.push_back(newState);
}

void StatesManager::popState()
{
	states.back()->cleanup();
	delete states.back();
	states.pop_back();

	if (states.empty())
		running = false;
	else
		states.back()->resume();
}

void StatesManager::changeState(State* newState)
{
	states.back()->cleanup();
	delete states.back();
	states.back() = newState;
}

void StatesManager::quit()
{
	running = false;

	while (!states.empty())
		popState();
}

bool StatesManager::isRunning() const
{
	return running && window.isOpen();
}
