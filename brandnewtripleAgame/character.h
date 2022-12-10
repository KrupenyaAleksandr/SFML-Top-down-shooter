#pragma once
#include "entity.h"

class character : public entity
{
protected:
	int reload;
	int weapon;
	int hp;
public:
	character();
	virtual ~character();
};

