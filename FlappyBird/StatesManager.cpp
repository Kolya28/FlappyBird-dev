#include "pch.h"
#include "StatesManager.h"

void StatesManager::init(std::string dir, int h, int v, const std::string& title, bool fullscreen)
{
	this->dir = dir;
	running = true;

	hwnd = GetDesktopWindow();
	hdc = GetDC(hwnd);

	if (h == 0)
	{
		this->h = GetDeviceCaps(hdc, HORZRES);
		this->v = GetDeviceCaps(hdc, VERTRES);
	}
	else
	{
		this->h = h;
		this->v = v;
	}

	window.create(sf::VideoMode(this->h, this->v), title,
		(fullscreen ?
			sf::Style::Fullscreen :
			sf::Style::Default));

	defaultView = window.getDefaultView();

	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
}

void StatesManager::cleanup()
{
	quit();
	window.close();
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
	}

	if (userScaleChanged)
	{
		sf::Event t;
		t.type = sf::Event::Resized;
		handleEvent(t);
		userScaleChanged = false;
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
	newState->setEngine(this);
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

void StatesManager::setUserScale(float scale)
{
	userScale = scale;
	userScaleChanged = true;
}

