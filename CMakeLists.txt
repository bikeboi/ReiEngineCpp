cmake_minimum_required(VERSION 3.10)
project(Release)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/Lua)
include_directories(include/ReiLib)
include_directories(include/SFML)
include_directories(include/SFML/Audio)
include_directories(include/SFML/Graphics)
include_directories(include/SFML/Network)
include_directories(include/SFML/System)
include_directories(include/SFML/Window)
include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

# Find and add SFML

add_executable(Release
        src/AnimSystem.cpp
        src/AnimSystem.h
        src/AssetManager.cpp
        src/AssetManager.h
        src/AudioSystem.cpp
        src/AudioSystem.h
        src/CollisionSystem.cpp
        src/CollisionSystem.h
        src/CompManager.cpp
        src/CompManager.h
        src/Components.h
        src/Engine.cpp
        src/Engine.h
        src/Entity.h
        src/EntityManager.cpp
        src/EntityManager.h
        src/InputModules.h
        src/InputSystem.cpp
        src/InputSystem.h
        src/main.cpp
        src/PhysicsSystem.cpp
        src/PhysicsSystem.h
        src/RenderSystem.cpp
        src/RenderSystem.h
        src/Scene.cpp
        src/Scene.h
        src/SceneMachine.cpp
        src/SceneMachine.h
        src/ScriptSystem.cpp
        src/ScriptSystem.h
        src/System.h
        src/Utility.h)
