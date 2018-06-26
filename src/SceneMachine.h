#pragma once

#include <memory>
#include <vector>

#define SOL_CHECK_ARGUMENTS
#include <Lua/sol.hpp>
#include <ReiLib/pmap.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Scene.h"
#include "EntityManager.h"
#include "CompManager.h"

#define INIT_SCENE_PATH "scripts/Scenes/INIT_SC.lua"

class SceneMachine
{
private:
	struct SceneState {
		SceneState(): name(""), fileName("") {}
		SceneState(std::string nm, std::string fName): name(nm), fileName(fName) {}
		std::string name;
		std::string fileName;
		std::vector<sf::Int32> paths;
	};

public:
	SceneMachine(EntityManager& eManager, CompManager& cManager);
	~SceneMachine() { closeScene(); }
	void init();
	bool update();
	Scene& getScene() { return *(active_scene.get()); }
	std::shared_ptr<Scene> getScenePtr() { return active_scene; }
	void closeScene();

private:
	std::shared_ptr<Scene> active_scene;
	SceneState active_state;
	rei::pmap<sf::Int32, SceneState> state_list;
	EntityManager& eMan;
	CompManager& cMan;
	sol::state lua;
};

