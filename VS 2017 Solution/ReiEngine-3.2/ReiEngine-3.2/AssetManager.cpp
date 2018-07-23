#include <iostream>

#include "AssetManager.h"
#include "Utility.h"

AssetManager::AssetManager()
{
	defaultTex.loadFromFile(DEFAULT_TEXTURE); 
	defaultFont.loadFromFile(DEFAULT_FONT);
}

// Loads up texture from
bool AssetManager::loadTex(sf::Int32 name, std::string texpath)
{
	if (texMap.check(name)) {
		std::cout << "ASSET MANAGER: Texture ->" << name << "already exists" << std::endl;
		return true;
	}
	if (!texBuffer.loadFromFile(ASSETS + texpath))
	{
		// If loading fails, we load a reference to the default texture
		// alongside the name, in the texture map
		auto& defaultTexRef = defaultTex;
		texMap.push(name, defaultTexRef);
		return false;
	}
	texMap.push(name, texBuffer);
	return true;
}

// Fetches reference to loaded texture in texture map
sf::Texture& AssetManager::getTex(sf::Int32 tCode)
{
	if (texMap.check(tCode))
	{
		return texMap.get(tCode);
	}
	return defaultTex;
}

// Loads font into texture map
bool AssetManager::loadFont(std::string name)
{
	if (!fontBuffer.loadFromFile(FONT_PATH + name + ".ttf"))
	{
		auto& defaultFontRef = defaultFont;
		fontMap.push(Util::strHash(name), defaultFontRef);
		return false;
	}
	fontMap.push(Util::strHash(name), fontBuffer);

	return true;
}

// Fetches reference to loaded font in font map
sf::Font& AssetManager::getFont(sf::Int32 fCode)
{
	if (fontMap.check(fCode))
	{
		return fontMap.get(fCode);
	}
	return defaultFont;
}