#pragma once

#include "System.h"
#include "CompManager.h"

/* 
 * AnimSystem
 * Animation system. Increments all the anim components
*/

class AnimSystem: public System
{
public:
	AnimSystem();
	~AnimSystem();
	void update(CompManager& cMan);
	
};

