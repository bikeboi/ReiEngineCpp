#include "PhysicsSystem.h"


PhysicsSystem::PhysicsSystem()
{
	airRes = 0.9f;
}


PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::apply(CompManager& cMan)
{
	for (auto& pCompPair : cMan.physicsMap.getMap())
	{
		auto& owner = pCompPair.first;
		auto& pComp = cMan.physicsMap.get(owner);
		//std::cout << "VEL: " << pComp.cVel.x << " " << pComp.cVel.y << std::endl;

		//Do collision stuff
		if (cMan.checkComponent<COMP::COLLISION>(owner) && cMan.collisionMap.get(owner).mobile == true)
		{
			//Top
			if (cMan.collisionMap.get(owner).top.second && pComp.cVel.y < 0) 
			{ 
				//std::cout << "PHYSICS STOP TOP" << std::endl;
				pComp.cVel.y = 0; 
			} 

			//Right
			if (cMan.collisionMap.get(owner).right.second && pComp.cVel.x > 0)
			{
				//std::cout << "PHYSICS STOP RIGHT" << std::endl;
				pComp.cVel.x = 0;
			}

			//Left
			if (cMan.collisionMap.get(owner).left.second && pComp.cVel.x < 0)
			{
				//std::cout << "PHYSICS STOP LEFT" << std::endl;
				pComp.cVel.x = 0;
			}

			//Bot
			if (cMan.collisionMap.get(owner).bottom.second && pComp.cVel.y > 0)
			{
				//std::cout << "PHYSICS STOP BOT" << std::endl;
				pComp.cVel.y = 0;
			}
		}

		//Apply velocity to position
		if (cMan.checkComponent<COMP::TRANSFORM>(owner))
		{
			//std::cout << "VEL : " << pComp.second.cVel.x << " " << pComp.second.cVel.y << std::endl;
			cMan.transformMap.get(owner).pos.x += pComp.cVel.x;
			cMan.transformMap.get(owner).pos.y += pComp.cVel.y;
		}

		//Update Previous Velocity
		pComp.pVel = pComp.cVel;

		//Dampen Velocity
		pComp.cVel.x *= airRes;
		pComp.cVel.y *= airRes;
		if (abs(pComp.cVel.x) < MIN_VEL) { pComp.cVel.x = 0; } 
		if (abs(pComp.cVel.y) < MIN_VEL) { pComp.cVel.y = 0; }
	}
}