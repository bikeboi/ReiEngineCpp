#include <iostream>
#include <cmath>

#include "CollisionSystem.h"

CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

bool CollisionSystem::resolve(CompManager& cMan)
{
	bool coll = false;
	bool right = false, top = false, bot = false, left = false;
	for (auto& colCompPairA : cMan.collisionMap.getMap())
	{
		auto& ownerA = colCompPairA.first;
		auto& colCompA = cMan.collisionMap.get(ownerA);
		//Check Collision
		for (auto& colCompPairB : cMan.collisionMap.getMap())
		{
			auto& ownerB = colCompPairB.first;
			auto& colCompB = cMan.collisionMap.get(ownerB);

			//std::cout << "A B ->" << ownerA << " " << ownerB << std::endl;
			if (ownerA != ownerB)
			{
				//std::cout << "ORIGIN DIFF = " << abs(colCompA.second.origin.x - colCompB.second.origin.x) << std::endl;
				auto colD = checkCollision(cMan, ownerA, ownerB);
				if (std::get<0>(colD))
				{
					//std::cout << "COLLISION DETECTED" << std::endl;
					//std::cout << "COLLIDING ";
					coll = true;
					//SIDE COLLISION CHECKING
					if (colCompA.solid && colCompB.solid)
					{
						//std::cout << colCompA.first << " is solid = " << colCompA.second.solid << std::endl;
							float wy = std::get<1>(colD) * std::get<4>(colD);
							float hx = std::get<2>(colD) * std::get<3>(colD);

							if (wy > hx)
							{
								if (wy > -hx)
								{
									//std::cout << "TOP" << std::endl;
									colCompA.setSide(COMP::COLLISION::TOP_SIDE, ownerB, true);
									top = true;
								}
								else
								{
									//std::cout << "RIGHT" << std::endl;
									colCompA.setSide(COMP::COLLISION::RIGHT_SIDE, ownerB, true);
									right = true;
									
								}
							}
							else {
								if (wy > -hx)
								{
									//std::cout << "LEFT" << std::endl;
									colCompA.setSide(COMP::COLLISION::LEFT_SIDE, ownerB, true);
									left = true;
								}
								else
								{
									//std::cout << "BOTTOM" << std::endl;
									colCompA.setSide(COMP::COLLISION::BOT_SIDE, ownerB, true);
									bot = true;
								}

							}
						}
					} else { /*std::cout << "NO COLLIDING OBJECTS FOUND" << std::endl;*/ }
				}
				else {
					//Clear undetected collisions
					//std::cout << "RESETTING COLLISIONS" << std::endl;
					if (!top) { colCompA.setSide(COMP::COLLISION::TOP_SIDE, 0, false); }
					if (!right) { colCompA.setSide(COMP::COLLISION::RIGHT_SIDE, 0, false); }
					if (!bot) { colCompA.setSide(COMP::COLLISION::BOT_SIDE, 0, false); }
					if (!left) { colCompA.setSide(COMP::COLLISION::LEFT_SIDE, 0, false); }
				}
			}
		}

	return coll;
}

std::tuple<bool, float, float, float, float> CollisionSystem::checkCollision(CompManager& cMan, short idA, short idB) const
{
	auto& colA = cMan.collisionMap.get(idA);
	auto& colB = cMan.collisionMap.get(idB);

	float w = colA.halfSize.x + colB.halfSize.x;
	float h = colA.halfSize.y + colB.halfSize.y;

	float velAX = 0;
	float velAY = 0;
	float velBX = 0;
	float velBY = 0;

	//std::cout << "A B -> " << idA << " " << idB << std::endl;

	if (cMan.checkComponent<COMP::PHYSICS>(idA) && cMan.checkComponent<COMP::PHYSICS>(idB))
	{
		//std::cout << "CHECKING PHYSICS VEL FOR COLL" << std::endl;
		velAX += cMan.physicsMap.get(idA).cVel.x;
		velAY += cMan.physicsMap.get(idA).cVel.y;
		velBX += cMan.physicsMap.get(idB).cVel.x;
		velBY += cMan.physicsMap.get(idB).cVel.y;
	}
	

	float dx = (colA.origin.x + velAX) - (colB.origin.x + velBX);
	float dy = (colA.origin.y + velBY) - (colB.origin.y + velBY);

	bool xColl = abs(dx) <= w;
	bool yColl = abs(dy) <= h;

	return std::make_tuple(xColl && yColl, w, h, dx, dy);
}