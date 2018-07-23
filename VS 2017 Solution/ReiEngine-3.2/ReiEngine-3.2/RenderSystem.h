#pragma once

#include <iostream>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "System.h"
#include "CompManager.h"
#include "Scene.h"

#define FPS_FONT "core/sansation.ttf"

class RenderSystem: public System
{
public:
	RenderSystem(sf::Uint16 height, sf::Uint16 width);
	~RenderSystem();
	bool isFocused() { return focused; }
	void render(CompManager& cMan, std::shared_ptr<Scene> activeScene, sf::Uint16 frameTime);
	void renderTree(CompManager& cMan, const SC::Node& rootNode);
	void renderCollBoxes(rei::pmap<short, COMP::COLLISION> collMap);
	void drawFps(sf::Uint16 frames);

private:
	sf::RenderWindow window;
	sf::Event winEvent;
	sf::RectangleShape px;
	bool focused;
	bool drawColls;
	bool showFps;
	sf::Text fpsText;
	sf::Font fpsFont;
};

