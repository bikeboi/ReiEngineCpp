#pragma once

#include <tuple>
#include "CompManager.h"

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();
	bool resolve(CompManager& cMan);
	std::tuple<bool, float, float, float, float> checkCollision(CompManager& cMan, short idA, short idB) const;

private:
	
};

