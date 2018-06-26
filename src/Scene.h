#pragma once

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "Utility.h"
#include "CompManager.h"
#include "EntityManager.h"


#define SCENE_SCRIPT_PATH "scripts/Scenes/"

namespace SC
{
	struct Node
	{
		Node() : parent(nullptr), trans(nullptr), id(0) {}
		Node(Node& p, sf::Int32 owner): parent(std::make_shared<Node>(p)), id(owner) {}
		Node(Node& p, sf::Int32 owner, COMP::TRANSFORM& transform, sf::Vector2f offS) : trans(std::make_shared<COMP::TRANSFORM>(transform)), id(owner), parent(std::make_shared<Node>(p)), offset(offS) {}
		sf::Int32 id;
		sf::Vector2f offset;
		std::shared_ptr<COMP::TRANSFORM> trans;
		std::vector<Node> children;
		std::shared_ptr<Node> parent;
	};
}

class Scene
{
public:
	Scene(sf::Int32 id, std::string script, CompManager& cMan, EntityManager& eMan);
	~Scene() {}
	void update();
	std::pair<bool, sf::Int32>& getStatus();
	void next(std::string next_scene);
	void build(sol::table& data, SC::Node& p, CompManager& cMan, EntityManager& eMan);
	SC::Node& getRoot() { return root; } 
	// Weird bug prevents me from making this private

private:
	sf::Int32 id;
	sol::function scrUpdate;
	SC::Node root;
	std::pair<bool, sf::Int32> terminate;
};

