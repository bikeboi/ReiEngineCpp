#include "ScriptSystem.h"
#include "Utility.h"
#include "Scene.h"

using KEYBOARD = sf::Keyboard;


ScriptSystem::~ScriptSystem()
{
}

void ScriptSystem::buildInterface()
{
	// Exposes relevant component functions to the lua scripts being loaded

	//Expose input keys
	lua.new_enum("KEY",
		"Up", KEYBOARD::Up,
		"Down", KEYBOARD::Down,
		"Left", KEYBOARD::Left,
		"Right", KEYBOARD::Right,
		"W", KEYBOARD::W,
		"A", KEYBOARD::A,
		"S", KEYBOARD::S,
		"D", KEYBOARD::D,
		"N", KEYBOARD::N,
		"Esc", KEYBOARD::Escape
	);

	//Input Reading
	lua.set_function("getKey", &COMP::CONTROLLER::getKey);

	//Position Setting
	lua.set_function("move", &COMP::TRANSFORM::setPos);
	lua.set_function("getX", &COMP::TRANSFORM::getX);
	lua.set_function("getY", &COMP::TRANSFORM::getY);

	//Physics Setting
	lua.set_function("addVel", &COMP::PHYSICS::addVel);

	//Audio Setting
	lua.set_function("playSound", &COMP::AUDIO::setActive);

	//Anim Functions
	lua.set_function("setAnim", &COMP::ANIM::setFrame);
	lua.set_function("setAnimSpeed", &COMP::ANIM::setSpeed);

	//Render Functions
	lua.set_function("rotate", &COMP::RENDER::rotate);
	lua.set_function("showText", &COMP::RENDER::showText);
	lua.set_function("setText", &COMP::RENDER::setText);

	//Scene Functions
	lua.set_function("nextScene", &Scene::next);
}

void ScriptSystem::load(CompManager& cMan, Scene& active_scene)
{
	//Set Update and Init Functions
	for (auto& sCompPair : cMan.scriptMap.getMap())
	{
		auto& owner = sCompPair.first;
		auto& sComp = cMan.scriptMap.get(owner);

		//Expose active scene
		lua.set("ActiveScene", &active_scene);

		if (cMan.checkComponent<COMP::CONTROLLER>(owner)) lua.set("Input", cMan.controllerMap.get(owner));
		if (cMan.checkComponent<COMP::RENDER>(owner)) { lua.set("Render", &cMan.renderMap.get(owner)); }
		if (cMan.checkComponent<COMP::ANIM>(owner)) { lua.set("Anim", &cMan.animMap.get(owner)); }
		if (cMan.checkComponent<COMP::TRANSFORM>(owner)) { lua.set("Trans", &cMan.transformMap.get(owner)); }
		if (cMan.checkComponent<COMP::PHYSICS>(owner)) { lua.set("Phys", &cMan.physicsMap.get(owner)); }
		if (cMan.checkComponent<COMP::AUDIO>(owner)) { lua.set("Aud", &cMan.audioMap.get(owner)); }

		sol::load_result lr = lua.load_file(SCRIPT_PATH + sComp.path);
		//std::cout << "Loading -> " << SCRIPT_PATH + sComp.script << std::endl;
		if (lr.valid())
		{
			lua.safe_script_file(SCRIPT_PATH + sComp.path);
			if (Util::checkVar("Init", lua)) { sComp.Init = lua["Init"]; }
			if (Util::checkVar("Update", lua)) { sComp.Update = lua["Update"]; }
		}
		else {
			std::cout << "SCRIPT LOAD ERROR: " << SCRIPT_PATH + sComp.path << std::endl;
		}
		if (sComp.Init.valid()) { sComp.Init(); }
	}
}

void ScriptSystem::run(CompManager& cMan, Scene& active_scene)
{
	for (auto& sCompPair : cMan.scriptMap.getMap())
	{
		auto& owner = sCompPair.first;
		auto& sComp = cMan.scriptMap.get(owner);

		//Expose active scene
		lua.set("ActiveScene", &active_scene);

		//Expose Components by reference
		if (cMan.checkComponent<COMP::CONTROLLER>(owner)) lua.set("Input", cMan.controllerMap.get(owner));
		if (cMan.checkComponent<COMP::RENDER>(owner)) lua.set("Rend", &cMan.renderMap.get(owner)); 
		if (cMan.checkComponent<COMP::ANIM>(owner)) lua.set("Anim", &cMan.animMap.get(owner)); 
		if (cMan.checkComponent<COMP::TRANSFORM>(owner)) lua.set("Trans", &cMan.transformMap.get(owner)); 
		if (cMan.checkComponent<COMP::PHYSICS>(owner)) lua.set("Phys", &cMan.physicsMap.get(owner)); 
		if (cMan.checkComponent<COMP::AUDIO>(owner)) lua.set("Aud", &cMan.audioMap.get(owner)); 
		
		//std::cout << "COMPONENTS SET" << std::endl;
		if (sComp.Update.valid()) { sComp.Update(); }
	}
}
