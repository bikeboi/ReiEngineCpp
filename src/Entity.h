#pragma once

#include <string>

class Entity
{
public:
	Entity() {}
	Entity(short eId, short eType): id_(eId), type_(eType) { }
	virtual ~Entity() {}
	const short& getId() { return id_; }
	const short& getType() { return type_; }
	

protected:
	std::string name;
	short id_;
	short type_;

};

