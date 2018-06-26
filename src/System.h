#pragma once
class System
{
public:
	virtual ~System() {}
	const unsigned int getId() { return id; }

protected:
	unsigned int id;
};

