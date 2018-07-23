#include "AudioSystem.h"

void AudioSystem::play(rei::pmap<short, COMP::AUDIO>& audioMap)
{
	for (auto& audCompPair : audioMap.getMap())
	{
		auto& owner = audCompPair.first;
		auto& audComp = audioMap.get(audCompPair.first);
		if (audComp.playSound)
		{ 
			if (audComp.delay <= 0)
			{
				audComp.activeSound.play();
				audComp.delay = audComp.activeDelay;
			}
			else {
				if (audComp.delay != 0) { audComp.delay -= 16; }
			}
			audComp.playSound = false; 
		}
		else {
			audComp.delay = 0;
		}
	}
}