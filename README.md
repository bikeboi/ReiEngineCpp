# Rei-Engine 0.4

> A simple scriptable 2D game engine

## Overview
ReiEngine is intended to be a reasonably fast 2D game engine that developers can
create games in with Lua. Though you may be reading this on a supposed `release` branch, do
not be fooled. This project has not been (and may never) be released.

## Using the engine
It's currently only built for Windows.
All you need to do is run the `ReiEngine-3.2` executable in the `bin` 
directory and have fun :D.
There's no 'structure' as such to the locations for resource files and scripts, but the locations can be easily changed
in the macros of the `ResourceManager` class (this requires rebuilding the engine though).
For now, default locations for scripts assets and other things can be found in the [bin](./bin)
folder.

## Scripting
By default, the script folder must be located within the same directory 
as the executable, with the directory structure as shown in the default 
`scripts` folder. The `EntityTypes` `INIT_SC` and `TextureLoad` scripts 
are mandatory for the engine to load entities, scenes and textures 
respectively. Behaviour scripts for each entity can then be added or 
removed freely within the given behaviour scripts folder (default is [here](./bin/scripts/Behaviour/)).

## Building
Due to my drastically misinformed choice of operating system at the time, the engine
is currently only built for windows. However, you're welcome to try and wangle the libraries
and Lua bindings for a different OS.

## License
[MIT](./LICENSE)
