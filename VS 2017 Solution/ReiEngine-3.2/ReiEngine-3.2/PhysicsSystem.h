#pragma once

#include <cmath>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "CompManager.h"

#define MIN_VEL pow(10, -7)

class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void apply(CompManager& cMan);

private:
	float airRes;
};

