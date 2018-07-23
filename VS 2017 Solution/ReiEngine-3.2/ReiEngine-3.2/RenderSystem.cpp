#include "RenderSystem.h"
#include "Scene.h"

RenderSystem::RenderSystem(sf::Uint16 width, sf::Uint16 height): window(sf::VideoMode(width, height), "Game Window", sf::Style::Close)
{
	showFps = true;
	focused = true;
	drawColls = true; // <- Draw Collision Boxes
	px.setSize(sf::Vector2f(10, 10));
	px.setFillColor(sf::Color::White);
	fpsFont.loadFromFile("core/fonts/sansation.ttf");
	fpsText.setFont(fpsFont);
	fpsText.setPosition(5, 0);
	fpsText.setScale(0.5, 0.5);
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::render(CompManager& cMan, std::shared_ptr<Scene> activeScene, sf::Uint16 frameTime) 
{
	if (window.isOpen())
	{
		while (window.pollEvent(winEvent))
		{
			if (winEvent.type == sf::Event::Closed)
			{
				std::cout << "Closing Window" << std::endl;
				window.close();
			}
			if (winEvent.type == sf::Event::LostFocus)
			{
				focused = false;
				std::cout << "Window Lost Focus" << std::endl;
			}
			if (winEvent.type == sf::Event::GainedFocus)
			{
				focused = true;
				std::cout << "Window Gained Focus" << std::endl;
			}
		}
		window.clear(sf::Color::Black);

		if (activeScene) renderTree(cMan, activeScene->getRoot());
		if (drawColls) renderCollBoxes(cMan.collisionMap);
		if (showFps) drawFps(frameTime);
		window.display();
	}
}

void RenderSystem::renderTree(CompManager& cMan, const SC::Node& rootNode)
{
	//std::cout << "RENDER ROOT = " << rootNode.id << std::endl;
	if (rootNode.id != 0)
	{
		//std::cout << "Drawing " << rootNode.id << std::endl;
		
		if (cMan.checkComponent<COMP::RENDER>(rootNode.id))
		{
			window.draw(cMan.renderMap.get(rootNode.id).sprite);
			if (cMan.fetch<COMP::RENDER>(rootNode.id).tVisible) window.draw(cMan.renderMap.get(rootNode.id).text);
		} 
	}
	
	for (const auto& node : rootNode.children)
	{
		renderTree(cMan, node);
	} 
}

void RenderSystem::renderCollBoxes(rei::pmap<short, COMP::COLLISION> collMap)
{
	sf::Color boxColor(0, 255, 0, 35);
	sf::Color boxLine(0, 255, 0, 255);
	for (auto& collPair : collMap.getMap())
	{
		auto& owner = collPair.first;
		auto& collComp = collMap.get(owner);

		px.setPosition({ collComp.AABB.left, collComp.AABB.top });
		px.setSize({ collComp.AABB.width, collComp.AABB.height });
		px.setFillColor(boxColor);
		px.setOutlineColor(boxLine);
		px.setOutlineThickness(1);
		window.draw(px);
		//std::cout << "DRAWING " << owner << "COLL SIZE " << collComp.AABB.width << " " << collComp.AABB.height << std::endl;
	}
	//px.setSize({ 1, 1 });
}

void RenderSystem::drawFps(sf::Uint16 frames)
{
	std::string fpsDisplay = /*"Time per frame: " + std::to_string(frames) + "ms\n" + */ "Frames per second: " + std::to_string(1000/frames);
	fpsText.setString(fpsDisplay);
	window.draw(fpsText);
}