#include <memory>

#include "InputSystem.h"
#include "InputModules.h"

InputSystem::InputSystem()
{
	joyCount = 0;
}


InputSystem::~InputSystem()
{
}

void InputSystem::init(rei::pmap<short, COMP::CONTROLLER>& inpMap)
{
	//std::cout << "Initializing " << inpMap.getMap().size() << " controller comps." << std::endl;
	for (auto& inpPair : inpMap.getMap())
	{
		auto& owner = inpPair.first;
		auto& inp = inpMap.get(owner);

		//Assign joystick sources
		if (joyCount < 4 && inp.source == INP::JOY)
		{
			inp.source = ++joyCount;
		}

		//Init Modules
		if (inp.mod == INP::MOVE)
		{
			if (inp.source == INP::SOURCE::KEY) {
				inp.keyMap = std::make_shared<std::map<sf::Keyboard::Key, bool>>(INP::MoveModule.keyMap);
				//std::cout << owner << "INP: loaded MOVE module" << std::endl;
			}
			else {
				//std::cout << "INP: MOVE module has no valid source. Entity=" << owner << std::endl;
			}
		}
		else if (inp.mod == INP::MODULE::MENU) {
			inp.keyMap = std::make_shared<std::map<sf::Keyboard::Key, bool>>(INP::MenuModule.keyMap);
			//std::cout << owner << "INP: loaded MENU module" << std::endl;
		}
		

		/*
		switch (inp.mod)
		{
		case INP::MOVE:
			if (inp.source == INP::SOURCE::KEY) {
				inp.keyMap = std::make_shared<std::map<sf::Keyboard::Key, bool>>(INP::MoveModule.keyMap);
				std::cout << owner << "INP: loaded MOVE module" << std::endl;
			}
			else {
				std::cout << "INP: MOVE module has no valid source. Entity=" << owner << std::endl;
			}
			break;

		case INP::MENU:
			inp.keyMap = std::make_shared<std::map<sf::Keyboard::Key, bool>>(INP::MenuModule.keyMap);
			std::cout << "INP: loaded MENU module" << std::endl;
			break;

		default:
			std::cout << owner << ": No INPUT MODULE found." << std::endl; // <- Default goes here 
		} */
	}
}

void InputSystem::handleInput(rei::pmap<short, COMP::CONTROLLER>& inpMap)
{
	for (auto& inpPair : inpMap.getMap())
	{
		auto& owner = inpPair.first;
		auto& inp = inpMap.get(owner);
		//Set Keys
		if (inp.keyMap != nullptr)
		{
			auto& kMap = *inp.keyMap.get();
			for (auto& kPair : kMap)
			{
				kPair.second = sf::Keyboard::isKeyPressed(kPair.first);
				//if (kPair.second) { std::cout << inp.first << " KEY IS PRESSED" << std::endl; }
			}
		}
	}
}