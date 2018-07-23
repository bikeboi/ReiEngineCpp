#include "Engine.h"

Engine::Engine(): ent_man(comp_man), render_sys(600, 600), scene_mach(ent_man, comp_man), scr_sys(comp_man)
{
	/*
		Initializes Scene FSM and entity and component managers
		Builds scripting interface and initializes systems with initSys()
	*/

	running = true;

	fixed_rate = 20;
	frame_counter = 0;

	ent_man.load("EntityTypes.lua", comp_man);

	/*
	sf::Music bgMus;
	bgMus.setLoop(true);
	bgMus.openFromFile("assets/music/test.wav");
	bgMus.play();
	*/ // <= Put this somewhere useful, later

	scene_mach.init();
	scr_sys.buildInterface();
	initSys();
}

void Engine::initSys()
{
	// Initializes systems that need initialization
	// Updates the render component positions
	// Updates the collision component positions

	scr_sys.load(comp_man, *scene_mach.getScenePtr());

	inp_sys.init(comp_man.controllerMap);

	comp_man.updateRender();

	anim_sys.update(comp_man);
}

void Engine::inputHandle()
{
	if (render_sys.isFocused()) {
		inp_sys.handleInput(comp_man.controllerMap);
	}
}

void Engine::update(sf::Int32 timeElapsed)
{ 
	//Update Scene
	//If scene changed, reinitialize systems
	if (scene_mach.update())
	{
		std::cout << "Reinitializing Systems" << std::endl;
		initSys();
		frame_counter = 0;
	}

	//Update 
	scr_sys.run(comp_man, *scene_mach.getScenePtr());
	coll_sys.resolve(comp_man);
	phys_sys.apply(comp_man);
	comp_man.updateCollision();

	//Fixed Update
	if (frame_counter >= fixed_rate)
	{
		fixedUpdate();
		frame_counter = 0;
		//std::cout << "TICK" << std::endl;
	}

	comp_man.updateRender();
	//Add frame counter
	++frame_counter;
}

void Engine::renderUpdate(sf::Int32 frameTime)
{
	//Render to screen
	render_sys.render(comp_man, scene_mach.getScenePtr(), frameTime);
}

void Engine::fixedUpdate()
{
	anim_sys.update(comp_man);
	audio_sys.play(comp_man.audioMap);
}

const bool Engine::isRunning()
{
	return running;
}

void Engine::kill()
{
	running = false;
}