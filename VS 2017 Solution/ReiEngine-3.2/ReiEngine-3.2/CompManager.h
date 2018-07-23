#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <ReiLib/pmap.h>
#include "Entity.h"
#include "Components.h"


class CompManager
{
public:
	CompManager();
	~CompManager();
	template<typename Comp>
	Comp& addComponent(sf::Int32 owner) { getMap<Comp>().push(owner, Comp()); return getMap<Comp>().get(owner); }
	template<typename Comp>
	void removeComponent(sf::Int32 owner) { getMap<Comp>().remove(owner); }
	template<typename Comp>
	bool checkComponent(sf::Int32 owner) { return getMap<Comp>().getMap().find(owner) != getMap<Comp>().getMap().end(); }
	template <typename Comp>
	Comp &fetch(sf::Int32 owner) 
	{
		if (getMap<Comp>().getMap().find(owner) == getMap<Comp>().getMap().end())
		{
			std::cout << "Entity ID:" << owner << std::endl;
			exit(69);
		}
		return getMap<Comp>().get(owner);
	}
	void removeEntity(sf::Int32 owner);
	void updateCollision();
	void updateRender();

	void clearComponents(); // <-- Spooooky

	//Indexing Maps
	rei::pmap<short, COMP::TRANSFORM> transformMap;
	rei::pmap<short, COMP::RENDER> renderMap;
	rei::pmap<short, COMP::CONTROLLER> controllerMap;
	rei::pmap<short, COMP::PHYSICS> physicsMap;
	rei::pmap<short, COMP::COLLISION> collisionMap;
	rei::pmap<short, COMP::SCRIPT> scriptMap;
	rei::pmap<short, COMP::ANIM> animMap;
	rei::pmap<short, COMP::AUDIO> audioMap;

private:
	template<typename Comp>
	rei::pmap<short, Comp>& getMap();
};

//Get Maps
template<>
inline rei::pmap<short, COMP::TRANSFORM>& CompManager::getMap<COMP::TRANSFORM>() { return CompManager::transformMap; }

template<>
inline rei::pmap<short, COMP::RENDER>& CompManager::getMap<COMP::RENDER>() { return CompManager::renderMap; }

template<>
inline rei::pmap<short, COMP::CONTROLLER>& CompManager::getMap<COMP::CONTROLLER>() { return CompManager::controllerMap; }

template<>
inline rei::pmap<short, COMP::PHYSICS>& CompManager::getMap<COMP::PHYSICS>() { return CompManager::physicsMap; }

template<>
inline rei::pmap<short, COMP::COLLISION>& CompManager::getMap<COMP::COLLISION>() { return CompManager::collisionMap; }

template<>
inline rei::pmap<short, COMP::SCRIPT>& CompManager::getMap<COMP::SCRIPT>() { return CompManager::scriptMap; }

template<>
inline rei::pmap<short, COMP::ANIM>& CompManager::getMap<COMP::ANIM>() { return CompManager::animMap; }

template<>
inline rei::pmap<short, COMP::AUDIO>& CompManager::getMap<COMP::AUDIO>() { return CompManager::audioMap; }
