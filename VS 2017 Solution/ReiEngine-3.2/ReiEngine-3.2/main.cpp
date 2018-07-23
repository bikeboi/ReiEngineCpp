#include <iostream>
#include <memory>

#include "Engine.h"

int main()
{
	std::unique_ptr<Engine> rei_engine = std::make_unique<Engine>();

	sf::Int32 frame_rate = 60;
	sf::Int32 frame_time = 1000 / frame_rate;

	sf::Time time;
	sf::Int32 timeElapsed;
	sf::Clock timer;

	while (rei_engine->isRunning())
	{
		rei_engine->inputHandle();
		time = timer.getElapsedTime();
		timeElapsed = time.asMilliseconds();
		while (timeElapsed < frame_time)
		{
			rei_engine->update(timeElapsed);
			time = timer.getElapsedTime();
			timeElapsed = time.asMilliseconds();
		}

		rei_engine->renderUpdate(timeElapsed);
		timer.restart();
	}

	return 0;
}