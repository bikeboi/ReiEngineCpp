#include <iostream>
#include <algorithm>

#include "EntityManager.h"
#include "AssetManager.h"
#include "Entity.h"
#include "Utility.h"

EntityManager::EntityManager(CompManager& cMan): cManRef(cMan)
{
	lua.open_libraries(sol::lib::base);

	lua.new_enum("INPUT_TYPE",
		"KEY", INP::SOURCE::KEY,
		"JOY", INP::SOURCE::JOY
	);

	lua.new_enum("INPUT_MODULE",
		"MOVE", INP::MODULE::MOVE,
		"MENU", INP::MODULE::MENU
	);
}


EntityManager::~EntityManager()
{
}

int EntityManager::load(std::string&& script, CompManager& cMan)
{
	int loadErr = 0;
	sol::load_result lr = lua.load_file(ENTITY_SCRIPT_PATH + script);
	if (lr.valid())
	{
		lua.safe_script_file(ENTITY_SCRIPT_PATH + script);

		if (Util::checkVar("ENTITIES", lua))
		{
			sol::table Entities = lua["ENTITIES"];

			//Entity Data
			std::string e_name;
			sf::Int32 e_type;

			for (auto& entity : Entities) 
			{ 
				sol::table entData;
				if (entData = static_cast<sol::table>(entity.second))
				{
					//std::cout << "CAST TO TABLE" << std::endl;
					if (Util::checkAtt("class", entData))
					{
						std::string type = entData["class"];
						e_type = Util::strHash(type);
					}

					EntityData eData;
					eData.type = e_type;

					//Component Loading
					sol::table compData;
					if (Util::checkAtt("components", entData))
					{
						compData = entData["components"];
						//Load Transform Component
						if (Util::checkAtt("TRANSFORM", compData))
						{
							float x = 0, y = 0, z = 0, sX = 0, sY = 0;
							sol::table transformData = compData["TRANSFORM"];
							if (Util::checkAtt("x", transformData)) { x = transformData["x"]; }
							if (Util::checkAtt("y", transformData)) { y = transformData["y"]; }
							if (Util::checkAtt("z", transformData)) { z = transformData["z"]; }
							if (Util::checkAtt("sX", transformData)) { sX = transformData["sX"]; }
							if (Util::checkAtt("sY", transformData)) { sY = transformData["sY"]; }
							eData.Transform = std::make_tuple(true, x, y, z, sX, sY);
						}
						if (Util::checkAtt("CONTROLLER", compData))
						{
							sol::table controllerData = compData["CONTROLLER"];
							INP::SOURCE src;
							INP::MODULE mod;
							if (Util::checkAtt("source", controllerData)) { src = controllerData["source"]; }
							if (Util::checkAtt("mod", controllerData)) { mod = controllerData["mod"]; }
							eData.Controller = std::make_tuple(true, mod, src);
						}
						bool physics = false;
						if (Util::checkAtt("PHYSICS", compData) && (physics = compData["PHYSICS"])) 
						{ 
							eData.Physics = std::make_tuple(physics);
						}
						if (Util::checkAtt("COLLISION", compData))
						{
							float x = 0, y = 0, wd = 0, ht = 0;
							bool solid = false, mobile = false;
							sol::table collData = compData["COLLISION"];
							if (Util::checkAtt("x", collData)) { x = collData["x"]; }
							if (Util::checkAtt("y", collData)) { y = collData["y"]; }
							if (Util::checkAtt("width", collData)) { wd = collData["width"]; }
							if (Util::checkAtt("height", collData)) { ht = collData["height"]; }
							if (Util::checkAtt("solid", collData)) { solid = collData["solid"]; }
							if (Util::checkAtt("mobile", collData)) { mobile = collData["mobile"]; }
							eData.Collision = std::make_tuple(true, x, y, wd, ht, solid, mobile);
						}
						if (Util::checkAtt("SCRIPT", compData))
						{
							std::string scriptPath = compData["SCRIPT"];
							eData.Script = std::make_tuple(true, scriptPath);
						}

						if (Util::checkAtt("AUDIO", compData))
						{
							sol::table audioTab = compData["AUDIO"];
							for (auto& solPair : audioTab)
							{
								sf::Int32 soundId = Util::strHash(solPair.first.as<std::string>());
								sf::SoundBuffer sBuff; 
								sBuff.loadFromFile(ENTITY_ASSET_PATH + solPair.second.as<std::string>());
								std::get<1>(eData.Audio).push(soundId, sBuff);
							}
							std::get<0>(eData.Audio) = true;
						}

						if (Util::checkAtt("ANIM", compData))
						{
							sol::table animData = compData["ANIM"];
							int rows = 0, cols = 0, width = 0, height = 0, spd = 0, pX = 0, pY = 0;
							if (Util::checkAtt("rows", animData)) { rows = animData["rows"]; }
							if (Util::checkAtt("cols", animData)) { cols = animData["cols"]; }
							if (Util::checkAtt("width", animData)) { width = animData["width"]; }
							if (Util::checkAtt("height", animData)) { height = animData["height"]; }
							if (Util::checkAtt("spd", animData)) { spd = animData["spd"]; }
							if (Util::checkAtt("pX", animData)) { pX = animData["pX"]; }
							if (Util::checkAtt("pY", animData)) { pY = animData["pY"]; }
							eData.Anim = std::make_tuple(true, rows, cols, width, height, spd, pX, pY);
						}
						if (Util::checkAtt("RENDER", compData)) 
						{ 
							sol::table renderData = compData["RENDER"];
							float xOffset = 0, yOffset = 0;
							sf::Uint32 size = 30;
							std::string fontName = "";
							if (Util::checkAtt("sprites", renderData))
							{
								sol::table spriteData = renderData["sprites"];
								for (auto& sprPair : spriteData)
								{
									std::get<1>(eData.Render).push_back(Util::strHash(sprPair.first.as<std::string>()));
									ass_man.loadTex(Util::strHash(sprPair.first.as<std::string>()), sprPair.second.as<std::string>());
								}
							}
							if (Util::checkAtt("text", renderData))
							{
								sol::table textData = renderData["text"];
								if (Util::checkAtt("size", textData)) { size = textData["size"]; }
								if (Util::checkAtt("x", textData)) { xOffset = textData["x"]; }
								if (Util::checkAtt("y", textData)) { yOffset = textData["y"]; }
								if (Util::checkAtt("font", textData)) { fontName = textData["font"]; ass_man.loadFont(fontName); }
							}
							std::get<2>(eData.Render) = Util::strHash(fontName);
							std::get<3>(eData.Render) = size;
							std::get<4>(eData.Render) = xOffset;
							std::get<5>(eData.Render) = yOffset;
							std::get<0>(eData.Render) = true;
						}
						if (entityTypes.getMap().find(e_type) == entityTypes.getMap().end())
						{
							entityTypes.push(e_type, eData);
							std::cout << "Adding Entity: " << e_type << std::endl;
						}
						
					}
				}
			}
		}
		else { std::cout << "ENTITY TABLE DOES NOT EXIST..." << std::endl; return 65; }
	}
	else {
		std::cout << "ERROR 69:\nENTITY MANAGER: INVALID SCRIPT LOADING - EntMan.loadEntites(script)" << std::endl;
		return 69;
	}

	std::cout << "ENTITY TYPES SUCCESSFULLY LOADED. Number of Entity Types =" << entityTypes.getMap().size() << std::endl;

	return loadErr;
}

bool EntityManager::create(sf::Int32 id, sf::Int32 type)
{
	if (entityTypes.getMap().find(type) == entityTypes.getMap().end())
	{
		std::cout << "NO ENTITY: " << type << " found..." << std::endl;
		return false;
	}

	auto& ent = entityTypes.get(type);

	//Load Transform 
	if (std::get<0>(ent.Transform)) 
	{
		cManRef.addComponent<COMP::TRANSFORM>(id).init
		(
			{std::get<1>(ent.Transform), std::get<2>(ent.Transform), std::get<3>(ent.Transform)},
			{std::get<4>(ent.Transform), std::get<5>(ent.Transform)}
		);
		std::cout << id << " type[" << type << "] : Loaded TRANSFORM Component" << std::endl;
	}

	//Load Controller 
	if (std::get<0>(ent.Controller))
	{
		cManRef.addComponent<COMP::CONTROLLER>(id).init(std::get<1>(ent.Controller), std::get<2>(ent.Controller));
		auto setMod = cManRef.fetch<COMP::CONTROLLER>(id).mod;
		std::cout << id << " type[" << type << "] : Loaded CONTROLLER Component" << std::endl;
	}

	//Load Physics 
	if (std::get<0>(ent.Physics))
	{
		cManRef.addComponent<COMP::PHYSICS>(id);
		std::cout << id << " type[" << type << "] : Loaded PHYSICS Component" << std::endl;
	}

	//Load Collision 
	if (std::get<0>(ent.Collision))
	{
		cManRef.addComponent<COMP::COLLISION>(id).init(
			{ std::get<1>(ent.Collision), std::get<2>(ent.Collision) },
			{ std::get<3>(ent.Collision), std::get<4>(ent.Collision) },
			std::get<5>(ent.Collision), std::get<6>(ent.Collision)
		);
		std::cout << id << " type[" << type << "] : Loaded COLLISION Component" << std::endl;
	}

	//Load Script
	if (std::get<0>(ent.Script))
	{
		cManRef.addComponent<COMP::SCRIPT>(id).load(std::get<1>(ent.Script));
		std::cout << id << " type[" << type << "] : Loaded SCRIPT Component " << std::endl;
	}

	//Load Audio
	if (std::get<0>(ent.Audio))
	{
		cManRef.addComponent<COMP::AUDIO>(id).sounds = std::get<1>(ent.Audio);
		std::cout << id << " type[" << type << "] : Loaded AUDIO Component" << std::endl;
	}

	//Load Anim
	if (std::get<0>(ent.Anim))
	{
		cManRef.addComponent<COMP::ANIM>(id).init(
			std::get<1>(ent.Anim), std::get<2>(ent.Anim),
			std::get<3>(ent.Anim), std::get<4>(ent.Anim),
			std::get<5>(ent.Anim),                        // <-Anim Speed
			std::get<6>(ent.Anim), std::get<7>(ent.Anim)
		);
		std::cout << id << " type[" << type << "] : Loaded ANIM Component" << std::endl;
	}

	//Load Render
	if (std::get<0>(ent.Render))
	{
		sf::Int32 texCode = 0, fontCode = 0;
		sf::Vector2f textPos{ std::get<4>(ent.Render), std::get<5>(ent.Render) };

		if (std::get<1>(ent.Render).size() > 0)
		{
			texCode = std::get<1>(ent.Render).at(0);
		}
		if (std::get<2>(ent.Render) != 0)
		{
			fontCode = std::get<2>(ent.Render);
		}
		cManRef.addComponent<COMP::RENDER>(id).init(ass_man.getTex(texCode), ass_man.getFont(fontCode), textPos);
		cManRef.fetch<COMP::RENDER>(id).text.setCharacterSize(std::get<3>(ent.Render));
		std::cout << id << " type[" << type << "] : Loaded RENDER Component" << std::endl;
	}
	return true;
}