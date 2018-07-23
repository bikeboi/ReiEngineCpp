#pragma once

#include <iostream>
#include <queue>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "System.h"
#include "CompManager.h"

using KEYBOARD = sf::Keyboard;

namespace INP
{
	enum MODULE
	{
		MOVE,
		MENU 
	};

	enum SOURCE
	{
		KEY,
		JOY
	};
}


class InputSystem: public System
{
public:
	InputSystem();
	~InputSystem();
	void init(rei::pmap<short, COMP::CONTROLLER>& inpMap);
	void handleInput(rei::pmap<short, COMP::CONTROLLER>& inpMap);

private:
	std::queue<sf::Keyboard::Key> inputStream;
	short joyCount;
};

