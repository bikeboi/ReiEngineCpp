#pragma once

#include "System.h"
#include "CompManager.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class AudioSystem: public System
{
public:
	AudioSystem() {}
	~AudioSystem() {}
	void play(rei::pmap<short, COMP::AUDIO>& audioMap);
};

