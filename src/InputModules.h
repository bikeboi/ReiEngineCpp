#pragma once

#include <map>
#include <string>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using KEYBOARD = sf::Keyboard;

namespace INP
{
	struct INPUTMOD
	{
		short modId;
	};

	struct MOVEMENT: public INPUTMOD 
	{
		MOVEMENT() {}
		std::map<KEYBOARD::Key, bool> keyMap 
		{
			{ KEYBOARD::Up, 0 },
			{ KEYBOARD::Down, 0 },
			{ KEYBOARD::Left, 0 },
			{ KEYBOARD::Right, 0 },
			{ KEYBOARD::W, 0 },
			{ KEYBOARD::A, 0 },
			{ KEYBOARD::S, 0 },
			{ KEYBOARD::D, 0 }
		};
	} MoveModule;

	struct MENU : public INPUTMOD
	{
		std::map<KEYBOARD::Key, bool> keyMap
		{
			{ KEYBOARD::Up, 0 },
			{ KEYBOARD::Down, 0 },
			{ KEYBOARD::Left, 0 },
			{ KEYBOARD::Right, 0 },
			{ KEYBOARD::Escape, 0},
			{ KEYBOARD::N, 0}
		};
	} MenuModule;
}