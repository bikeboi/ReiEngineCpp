# Rei-Engine 3.2

### Running the program
All you need to do is run the `ReiEngine-3.2` executable in the `bin` 
directory and have fun :D.

#### Scripting
By default, the script folder must be located within the same directory 
as the executable, with the directory structure as shown in the default 
`script` folder. The `EntityTypes` `INIT_SC` and `TextureLoad` scripts 
are mandatory for the engine to load entities, scenes and textures 
respectively. Behaviour scripts for each entity can then be added or 
removed freely within the `Behaviour` folder.
Default script paths and script names can be changed within the source 
and rebuilt. The macros for the script paths can be located in the 
header files of the systems requiring the scripts. For example; The 
`ENTITY_SCRIPT_PATH` macro can be found within `EntityManager.h`

### Building (currently Windows only)
The Visual Studio Solution and corresponding files can be found within 
the `VS 2017 Solution` folder. All the project's 
dependencies can be 
located within this folder, so extracting said folder and building it in 
a different directory should have no issues.

## License
This project is under an [MIT License](./LICENSE)
