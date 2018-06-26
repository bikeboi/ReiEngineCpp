#pragma once

#include <string>
#include <functional>

#define SCRIPT_PATH "scripts/Behaviour/"
#define SOL_CHECK_ARGUMENTS
#include <Lua/sol.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "System.h"
#include "CompManager.h"
#include "Scene.h"

class ScriptSystem: public System
{
public:
	ScriptSystem(CompManager& comp_man) : cMan(comp_man) {
		lua.open_libraries(sol::lib::base);
	}
	~ScriptSystem();
	void buildInterface();
	void load(CompManager& cMan, Scene& active_scene);
	void run(CompManager& cMan, Scene& active_scene);

private:
	sol::state lua;
	
	template<typename Fn, typename ...Args>
	auto callWith(Fn fn) {
		return [&](sf::Int32 owner, Args... args) {
			std::cout << "Func Test: Running function with owner = " << owner << std::endl;
			fn(args...);
		};
	}

	CompManager& cMan;
};
