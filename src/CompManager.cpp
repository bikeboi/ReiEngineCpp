#include <algorithm>
#include <cmath>

#include "CompManager.h"


CompManager::CompManager()
{
}


CompManager::~CompManager()
{
}

void CompManager::removeEntity(sf::Int32 owner)
{
	//Remove Entity from all lists
	transformMap.remove(owner);
	scriptMap.remove(owner);
	controllerMap.remove(owner);
	renderMap.remove(owner);
	animMap.remove(owner);
	audioMap.remove(owner);
	collisionMap.remove(owner);
}

void CompManager::updateCollision()
{
	for (auto& colCompPair : collisionMap.getMap())
	{
		auto& owner = colCompPair.first;
		auto& colComp = collisionMap.get(owner);
		if (checkComponent<COMP::TRANSFORM>(owner))
		{
			colComp.setPos({ transformMap.get(owner).pos.x, transformMap.get(owner).pos.y });
			//if (owner == 1925) std::cout << owner << "-ORIGIN: " << colComp.origin.x << " " << colComp.origin.y << std::endl;
		}
	}
}

void CompManager::updateRender()
{
	for (auto& rCompPair : renderMap.getMap())
	{
		auto& owner = rCompPair.first;
		auto& rComp = renderMap.get(owner);
		if (checkComponent<COMP::TRANSFORM>(owner)) 
		{ 
			sf::Vector2f posDiff = { (transformMap.get(owner).pos.x + renderMap.get(owner).sprite.getOrigin().x), (transformMap.get(owner).pos.y + renderMap.get(owner).sprite.getOrigin().y) };
			rComp.updatePos(posDiff);
			rComp.sprite.setScale(copysign(transformMap.get(owner).scale.x, rComp.sprite.getScale().x), copysign(transformMap.get(owner).scale.y, rComp.sprite.getScale().y));
		}
	}
}

void CompManager::clearComponents()
{
	transformMap.clear();
	renderMap.clear();
	controllerMap.clear();
	physicsMap.clear();
	collisionMap.clear();
	scriptMap.clear();
	animMap.clear();
	audioMap.clear();
}