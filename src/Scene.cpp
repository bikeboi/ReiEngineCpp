#include "Scene.h"

Scene::Scene(sf::Int32 sceneId, std::string script, CompManager& cMan, EntityManager& eMan)
{
	id = sceneId;
	terminate = std::make_pair(false, 0);
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	sol::load_result lr = lua.load_file(SCENE_SCRIPT_PATH + script);
	if (lr.valid())
	{
		lua.safe_script_file(SCENE_SCRIPT_PATH + script);
		if (Util::checkVar("Tree", lua))
		{
			sol::table tree = lua["Tree"];
			build(tree, root, cMan, eMan);
		}
		else {
			std::cout << "SCENE: Cannot find Tree in script -> \"" << SCENE_SCRIPT_PATH + script  << "\"" << std::endl;
		}
		if (Util::checkVar("Update", lua))
		{
			scrUpdate = lua["Update"];
		}
		else {
			std::cout << "Scene: " << script << " No update function found" << std::endl;
		}
	}
	else {
		std::cout << "SCENE: \"" << SCENE_SCRIPT_PATH + script << "\" Invalid" << std::endl;
	}
	std::cout << "ROOT ID = " << root.id << std::endl;
}

void Scene::update()
{
	if (terminate.first)
	{
		terminate = std::make_pair(false, 0);
	}
}

std::pair<bool, sf::Int32>& Scene::getStatus()
{
	return terminate;
}

void Scene::next(std::string next_scene)
{
	//std::cout << "Terminating Scene: New Scene = " << next_scene << std::endl;
	terminate = std::make_pair(true, Util::strHash(next_scene));
}

void Scene::build(sol::table& data, SC::Node& p, CompManager& cMan, EntityManager& eMan)
{
	for (auto& dataPair : data)
	{
		sf::Int32 id = Util::strHash(dataPair.first.as<std::string>());
		sf::Int32 type = 0;
		float x = p.offset.x, y = p.offset.y, sX = 1, sY = 1;
		sol::table node = dataPair.second.as<sol::table>();

		//Get specialized entity data
		if (Util::checkAtt("class", node)) { type = Util::strHash(node["class"]); }
		if (Util::checkAtt("x", node)) { x += static_cast<float>(node["x"]); }
		if (Util::checkAtt("y", node)) { y += static_cast<float>(node["y"]); }
		if (Util::checkAtt("sX", node)) { sX = node["sX"]; }
		if (Util::checkAtt("sY", node)) { sY = node["sY"]; }

		std::cout << id << ": x = " << x << " y = " << y << std::endl;

		if (eMan.create(id, type))
		{
			SC::Node newNode;
			if (cMan.checkComponent<COMP::TRANSFORM>(id))
			{
				cMan.fetch<COMP::TRANSFORM>(id).pos = { x, y, cMan.fetch<COMP::TRANSFORM>(id).pos.z };
				cMan.fetch<COMP::TRANSFORM>(id).scale.x *= sX;
				cMan.fetch<COMP::TRANSFORM>(id).scale.y *= sY;
				newNode = SC::Node(p, id, cMan.fetch<COMP::TRANSFORM>(id), { x, y });
			}
			else {
				newNode = SC::Node(p, id);
			}
			
			if (Util::checkAtt("children", node))
			{
				sol::table children = node["children"];
				build(children, newNode, cMan, eMan);
			}
			p.children.push_back(newNode);
		}
		else { std::cout << "Building Node Failed. Cannot create entity: " << type << std::endl; } //Should almost never happen*
	}
}

// * It happened