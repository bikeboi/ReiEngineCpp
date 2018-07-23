#include <algorithm>

#include "SceneMachine.h"
#include "Utility.h"

SceneMachine::SceneMachine(EntityManager& eManager, CompManager& cManager): eMan(eManager), cMan(cManager)
{
	//
}

void SceneMachine::init()
{
	lua.open_libraries(sol::lib::base);

	if (Util::valid_script(INIT_SCENE_PATH, lua))
	{
		lua.safe_script_file(INIT_SCENE_PATH);
		if (Util::checkVar("SCENES", lua))
		{
			sol::table scene_table = lua["SCENES"];
			for (auto& scenePair : scene_table)
			{
				std::string strId = scenePair.first.as<std::string>();
				sf::Int32 id = Util::strHash(strId);

				std::cout << "Loading Scene: " << strId << " id : " << id << std::endl;

				if (Util::checkAtt(strId, scene_table))
				{
					std::string name = "", file = "";
					sol::table new_scene = scene_table[strId];
					if (Util::checkAtt("name", new_scene)) name = new_scene["name"];
					if (Util::checkAtt("file", new_scene)) file = new_scene["file"];
					SceneState sc_state(name, file);
					if (Util::checkAtt("paths", new_scene))
					{
						sol::table path_table = new_scene["paths"];
						for (auto& path : path_table)
						{
							std::cout << "SCENE: " << strId << " adding to path => " << path.second.as<std::string>() << std::endl;
							sc_state.paths.push_back(Util::strHash(path.second.as<std::string>()));
						}
					}
					state_list.push(id, sc_state);
					if (Util::checkAtt("first", new_scene))
					{
						bool first_scene = new_scene["first"];
						if (first_scene)
						{
							std::cout << "ACTIVE SCENE: " << name << std::endl;
							active_scene = std::make_shared<Scene>(id, file, cMan, eMan);
							active_state = sc_state;
							std::cout << "SCENE STATE: Name[" << active_state.name << "] ID[" << id << "]" << std::endl;
						}
					}
					else {
					}
				}
			}
			std::cout << "SCENE MACHINE: Loaded " << state_list.getMap().size() << std::endl;
		}
		else {
			std::cout << "SCENE MACHINE: 'SCENE' table not found." << std::endl;
		}
	}
	else {
		std::cout << "SCENE MACHINE: Scene INIT not found or invalid." << std::endl;
	}
}

bool SceneMachine::update()
{
	bool change_success = false;
	if (active_scene->getStatus().first)
	{
		std::cout << "SCENE MACHINE: SCENE TERMINATED" << std::endl;
		sf::Int32 scene_id = active_scene->getStatus().second;

		if (state_list.find(scene_id) != state_list.getMap().end())
		{
			SceneState next_state = state_list.get(scene_id);
			std::cout << "Attemping scene change id => " << scene_id << std::endl;

			//Check if path is accessible
			if (std::find(active_state.paths.begin(), active_state.paths.end(), scene_id) != active_state.paths.end())
			{
				auto new_file = state_list;

				std::cout << "CLOSING SCENE" << std::endl;
				closeScene();
				std::cout << "OPENING SCENE" << std::endl;
				active_scene.reset(new Scene(scene_id, next_state.fileName, cMan, eMan));
				active_state = state_list.get(scene_id);
				std::cout << "SCENE STATE: Name[" << active_state.name << "] ID[" << scene_id << "]" << std::endl;
				change_success = true;
			}
			else {
				std::cout << "SCENE MACHINE: Path Name=[" << next_state.name << "] ID=[" << scene_id << "] not available..." << std::endl;
			}
		}
		else {
			std::cout << "SCENE: Scene: " << scene_id << " does not exist." << std::endl;
		}
	} 

	active_scene->update();

	return change_success;
}

void SceneMachine::closeScene()
{
	cMan.clearComponents();
}