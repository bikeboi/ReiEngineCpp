#pragma once

#define ENTITY_SCRIPT_PATH "scripts/Entities/"
#define ENTITY_ASSET_PATH "assets/"
#define SOL_CHECK_ARGUMENTS

#include <string>
#include <vector>
#include <tuple>

#include <Lua/sol.hpp>

#include "InputSystem.h"
#include "CompManager.h"

#define MAX_ENTITIES 64

class Entity;

struct EntityData
{
	EntityData()
	{
		std::get<0>(Transform) = false;
		std::get<0>(Controller) = false;
		std::get<0>(Physics) = false;
		std::get<0>(Collision) = false;
		std::get<0>(Script) = false;
		std::get<0>(Audio) = false;
		std::get<0>(Anim) = false;
		std::get<0>(Render) = false;
	}
	size_t type;
	std::tuple<bool, float, float, float, float, float> Transform;
	std::tuple<bool, INP::MODULE, INP::SOURCE> Controller;
	std::tuple<bool> Physics; //Tuple so we can add things later
	std::tuple<bool, float, float, float, float, bool, bool> Collision;
	std::tuple<bool, rei::pmap<sf::Int32, sf::SoundBuffer>> Audio;
	std::tuple<bool, std::string> Script;
	std::tuple<bool, int, int, int, int, int, int, int> Anim;
	std::tuple<bool, std::vector<sf::Int32>, sf::Int32, sf::Uint32, float, float> Render;
};

class EntityManager
{
public:
	EntityManager(CompManager& cMan);
	~EntityManager();
	int load(std::string&& script, CompManager& cMan);
	bool create(sf::Int32 id, sf::Int32 type);

private:
	rei::pmap<sf::Int32, EntityData> entityTypes;
	sol::state lua;
	CompManager& cManRef;
};

