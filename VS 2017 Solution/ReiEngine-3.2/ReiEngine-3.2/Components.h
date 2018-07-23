#pragma once

#include <map>
#include <memory>
#include <tuple>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Lua/sol.hpp>

#include "Utility.h"

/* NOTES
 * Components are all derived from a base COMPONENT CLASS
 * All components have an init() function, acts as constructor
*/

namespace COMP
{
	template<typename T>
	inline auto compType();

	// Base component class
	struct COMPONENT
	{
	protected:
		short ref_;
	};

	// Transform Component
	struct TRANSFORM : public COMPONENT
	{
		TRANSFORM() : scale(1, 1) {}
		void init(float xPos, float yPos, float zPos, float width, float height)
		{
			pos.x = xPos;
			pos.y = yPos;
			pos.z = zPos;
			scale.x = width;
			scale.y = height;
		}
		void init(sf::Vector3f position, sf::Vector2f factor)
		{
			pos = position;
			scale = factor;
		}

		void setPos(float x, float y) { pos.x += x; pos.y += y; }
		float getX() { return pos.x; }
		float getY() { return pos.y; }

		sf::Vector3f pos;
		sf::Vector2f scale;
	};

	// Controller Component
	struct CONTROLLER : public COMPONENT
	{
		CONTROLLER() {}
		void init(short inpMod, short inpType) { mod = inpMod; source = inpType; }
		bool getKey(sf::Keyboard::Key key)
		{
			if ((keyMap != nullptr) && (keyMap->find(key) != keyMap->end())) { return keyMap->at(key); }
			return false;
		}

		short mod;
		short source;
		std::shared_ptr<std::map<sf::Keyboard::Key, bool>> keyMap;
		std::shared_ptr<std::map<sf::Keyboard::Key, bool>> joyMap;
	};

	// Physics Component
	struct PHYSICS : public COMPONENT
	{
		PHYSICS() {}
		void addVel(float x, float y) 
		{ 
			cVel.x += x;
			cVel.y += y;
		}
		//void setVel(sf::Vector2f vel) { cVel = vel; }

		float maxVel = 1.0f;
		sf::Vector2f cVel, pVel;
	};
	// Collision Component
	struct COLLISION : public COMPONENT
	{
		enum SIDE
		{
			RIGHT_SIDE = 0,
			TOP_SIDE = 1,
			LEFT_SIDE = 2,
			BOT_SIDE = 3
		};

		COLLISION() {  }

		// Init Function, position, size, solid, and mobility
		void init(float x, float y, float wd, float ht, bool isSolid, bool isMobile)
		{
			AABB = { x, y, wd, ht };
			halfSize = { wd / 2, ht / 2 };
			origin = { AABB.left + halfSize.x, AABB.top + halfSize.y };
			solid = isSolid;
			mobile = isMobile;
		}

		// Overloaded Init function for using vectors
		void init(sf::Vector2f pos, sf::Vector2f size, bool isSolid, bool isMobile)
		{
			AABB = { pos, size };
			halfSize = { size.x / 2, size.y / 2 };
			origin = { AABB.left + size.x /2, AABB.top + size.y /2 };
			solid = isSolid;
			mobile = isMobile;
		}
		void setPos(sf::Vector2f pos)
		{
			AABB.left = pos.x;
			AABB.top = pos.y;
			origin = { AABB.left + halfSize.x, AABB.top + halfSize.y };
		}

		// Set side of collision and source of collision
		void setSide(short side, short id, bool coll)
		{
			switch (side)
			{
			case 0: right.first = id; right.second = coll; 
				break;
			case 1: top.first = id; top.second = coll; 
				break;
			case 2: left.first = id; left.second = coll;
				break;
			case 3: bottom.first = id; bottom.second =coll;
				break;
			}
		}

		sf::FloatRect AABB;
		sf::Vector2f origin;
		sf::Vector2f halfSize;
		std::pair<short, bool> right;
		std::pair<short, bool> left;
		std::pair<short, bool> top;
		std::pair<short, bool> bottom;
		bool solid;
		bool mobile;
	};

	// Script Component
	struct SCRIPT : public COMPONENT
	{	
		SCRIPT() {}
		void load(std::string fileName) 
		{ 
			path = fileName;
		}
		std::string path;
		sol::function Init;
		sol::function Update;
	};

	// Audio Component
	struct AUDIO : public COMPONENT
	{
		AUDIO(): playSound(false), delay(0) {}

		void loadSound(sf::Int32 id, sf::SoundBuffer sound)
		{
			sounds.push(static_cast<sf::Int32>(sounds.getMap().size()), sound);
		}

		void setActive(std::string sound, unsigned int setDelay)
		{
			if (sounds.getMap().find(Util::strHash(sound)) != sounds.getMap().end())
			{
				if (Util::strHash(sound) != current)
				{
					activeSound.setBuffer(sounds.get(Util::strHash(sound)));
					if (setDelay != activeDelay) { activeDelay = setDelay; }
					delay = 0;
					current = Util::strHash(sound);
				}
				playSound = true;
			}
			else { std::cout << "AUDCOMP: " << sound << " does not exist" << std::endl; }
		}

		void mute() { activeSound.setBuffer(silent); }

		bool playSound;
		int delay;
		int activeDelay;
		sf::Int32 current;
		sf::Sound activeSound;
		sf::SoundBuffer silent;
		rei::pmap<sf::Int32, sf::SoundBuffer> sounds;
	};

	// Anim Component
	struct ANIM : public COMPONENT
	{
		ANIM(): cnt(0) {}
		void init(int rowCnt, int colCnt, int fWidth, int fHeight, int speed = 10, int activeRow = 0, int activeCol = 0)
		{
			frameSize = { fWidth, fHeight };
			aIndex = { activeRow, activeCol };
			activeFrame = { aIndex, frameSize };
			rows = rowCnt;
			cols = colCnt;
			spd = speed;
		}
		void setFrame(int row, int column = 0)
		{
			aIndex = { row, column };
			activeFrame.top = aIndex.x * frameSize.y;
			activeFrame.left = aIndex.y * frameSize.x;
		}
		void setSpeed(int speed) { spd = speed; }
		void setCols(int columns) { cols = columns; }

		sf::IntRect activeFrame;
		sf::Vector2i frameSize;
		sf::Vector2i aIndex;
		int rows, cols;
		int spd, cnt;
	};

	// Render Component
	struct RENDER : public COMPONENT
	{
		RENDER(): tVisible(true) {  }
		void init(sf::Texture& tex, sf::Font& font, sf::Vector2f textPos)
		{
			sprite.setTexture(tex);
			text.setFont(font);
			tPos = textPos;
		}

		void rotate(sf::Int16 deg)
		{
			//sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
			sprite.setRotation(deg);
			//sprite.setOrigin(sprite.getLocalBounds().left, sprite.getLocalBounds().top);
		}

		void updatePos(sf::Vector2f pos)
		{
			sprite.setPosition(pos);
			text.setPosition({ pos.x + tPos.x, pos.y + tPos.y });
		}

		void centerOrigin() // <- Experimental
		{
			sprite.setOrigin(sprite.getGlobalBounds().width/2, sprite.getGlobalBounds().height/2);
		}

		//Testing
		std::string getName(std::string name) { return name; }

		void showText(bool val) { tVisible = val; }

		void setText(std::string str) { text.setString(str); }

		bool tVisible;
		sf::Text text;
		sf::Vector2f tPos;
		sf::Sprite sprite;
	};

	//Component Type Enums
	enum CompEnum {
		INPUT_TYPE,
		RENDER_TYPE,
		ANIM_TYPE,
		TRANS_TYPE,
		PHYSICS_TYPE,
		SCRIPT_TYPE,
		AUDIO_TYPE
	};

	//Returns type of component (template specialization)
	template<>
	inline auto compType<TRANSFORM>() {
		return CompEnum::TRANS_TYPE;
	}
	template<>
	inline auto compType<CONTROLLER>() {
		return CompEnum::INPUT_TYPE;
	}
	template<>
	inline auto compType<RENDER>() {
		return CompEnum::RENDER_TYPE;
	}
	template<>
	inline auto compType<ANIM>() {
		return CompEnum::TRANS_TYPE;
	}
	template<>
	inline auto compType<AUDIO>() {
		return CompEnum::AUDIO_TYPE;
	}
	template<>
	inline auto compType<PHYSICS>() {
		return CompEnum::PHYSICS_TYPE;
	}
	template<>
	inline auto compType<SCRIPT>() {
		return CompEnum::SCRIPT_TYPE;
	}
}