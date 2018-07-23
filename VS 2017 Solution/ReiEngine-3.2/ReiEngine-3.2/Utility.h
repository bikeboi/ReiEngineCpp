#pragma once

#include <string>
#include <iostream>

#define SOL_CHECK_ARGUMENTS
#include <Lua/sol.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define TEXTURE_PATH "assets/"

class Util
{
public:
	Util() {}
	~Util() {}
	static bool valid_script(std::string&& script, sol::state& luaState)
	{
		sol::load_result lr = luaState.load_file(script);
		std::cout << "Loading " << script << std::endl;
		return lr.valid();
	}
	static bool checkVar(std::string&& var, sol::state& luaState) {
		auto v = luaState[var];
		return v.valid();
	}

	static bool checkAtt(std::string&& att, sol::table& luaTable) {
		auto v = luaTable[att];
		return v.valid();
	}

	static bool checkAtt(std::string& att, sol::table& luaTable) {
		auto v = luaTable[att];
		return v.valid();
	}

	static int randomInt(int min, int max) {
		return 0;
	}

	static sf::Int32 strHash(std::string&& str) {
		if (str == "") { return 0; }
		short hash = 0;
		for (auto& c : str)
		{
			hash += static_cast<char>(c) * 7;
		}
		//std::cout << "UTIL: " << str << " hash = " << hash << std::endl;
		return hash;
	}

	static sf::Int32 strHash(std::string& str) {
		if (str == "") { return 0; }
		short hash = 0;
		for (auto& c : str)
		{
			hash += c * 7;
		}
		//std::cout << "UTIL: " << str << " hash = " << hash << std::endl;
		return hash;
	}
};

