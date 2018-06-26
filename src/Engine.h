#pragma once

#include <iostream>
#include <memory>

#include "System.h"

#include "Scene.h"

#include "Utility.h"
#include "RenderSystem.h"
#include "AudioSystem.h"
#include "AnimSystem.h"
#include "InputSystem.h"
#include "ScriptSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"

#include "SceneMachine.h"

#include "CompManager.h"
#include "EntityManager.h"

class Engine
{
public:
	Engine();
	~Engine() {}
	void initSys();
	void inputHandle();
	void update(sf::Int32 timeElapsed);
	void renderUpdate(sf::Int32 frameTime);
	void fixedUpdate();
	const bool isRunning();
	void kill();

private:
	CompManager comp_man;
	EntityManager ent_man;

	RenderSystem render_sys;
	AudioSystem audio_sys;
	AnimSystem anim_sys;
	InputSystem inp_sys;
	ScriptSystem scr_sys;
	PhysicsSystem phys_sys;
	CollisionSystem coll_sys;

	SceneMachine scene_mach;

	int fixed_rate;
	int frame_counter;

	bool running;
};
