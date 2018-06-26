#pragma once

#include <iostream>
#include <ReiLib/pmap.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define ASSETS "assets/"

#define FONT_PATH "core/fonts/"

#define DEFAULT_TEXTURE "assets/sprites/SPR_Default.png"
#define DEFAULT_FONT "core/fonts/sansation.ttf"

#define TEXTURE_SCRIPT "scripts/AssetLoad/TextureLoad.lua"

static class AssetManager
{
public:
	AssetManager();
	~AssetManager() {}
	bool loadTex(sf::Int32 name, std::string texpath);
	sf::Texture& getTex(sf::Int32 tCode);
	bool loadFont(std::string name);
	sf::Font& getFont(sf::Int32 fCode);

public:
	rei::pmap<sf::Int32, sf::Texture> texMap;
	rei::pmap<sf::Int32, sf::Font> fontMap;

	//Buffers
	sf::Texture texBuffer;
	sf::Font fontBuffer;

	//Defaults
	sf::Texture defaultTex;
	sf::Font defaultFont;
} ass_man;

