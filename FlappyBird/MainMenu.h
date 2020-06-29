#pragma once
#include "pch.h"
#include "Menu.h"
#include "ChangeNickMenu.h"
#include "ConnectState.h"

class MainMenu :
	public Menu
{
	void placeButtons() override
	{
		buttons.emplace_back("Play", [&]()
			{
				//std::cout << "Play\n";
				engine->pushState(new Game(false));

				pause();
			});

		buttons.emplace_back("Online", [&]()
			{
				//std::cout << "Online\n";
				engine->pushState(new ConnectState);

				pause();
			});

		buttons.emplace_back("Change nick", [&]() 
			{
				engine->pushState(new ChangeNickMenu(&scale));
				pause();
			});

		buttons.emplace_back("Exit", [&]() 
			{
				engine->popState();
			});
	}
};