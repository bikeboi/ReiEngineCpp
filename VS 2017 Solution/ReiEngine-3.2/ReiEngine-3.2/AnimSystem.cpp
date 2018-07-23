#include "AnimSystem.h"



AnimSystem::AnimSystem()
{
}


AnimSystem::~AnimSystem()
{
}

// Increments anim component counters
void AnimSystem::update(CompManager& cMan)
{
	for (auto& animPair : cMan.animMap.getMap())
	{
		auto& owner = animPair.first;
		auto& aComp = cMan.animMap.get(animPair.first);
		//Advance Frames
		//std::cout << "ANIM COUNT [ENT " << aComp.first << "] : " << aComp.second.cnt << std::endl;
		if (aComp.cnt == aComp.spd)
		{
			sf::IntRect& cFrame = aComp.activeFrame;
			if (aComp.aIndex.y + 1 < aComp.cols)
			{
				//std::cout << "SETTING FRAME COLUMN = " << aComp.second.aIndex.y + 1 << std::endl;
				aComp.setFrame(aComp.aIndex.x, ++aComp.aIndex.y);
				++aComp.aIndex.y;
			}
			else
			{
				aComp.aIndex.y = 0;
				aComp.setFrame(aComp.aIndex.x, aComp.aIndex.y);
			}	
			aComp.cnt = 0;
		}
		else { ++aComp.cnt; }

		//Apply to render component
		if (cMan.checkComponent<COMP::RENDER>(owner))
		{
			cMan.renderMap.get(owner).sprite.setTextureRect(aComp.activeFrame);
			//std::cout << "Frame = " << aComp.second.activeFrame.top << " " << aComp.second.activeFrame.left << " " << aComp.second.activeFrame.width << " " << aComp.second.activeFrame.height << std::endl;
		}
	}
}