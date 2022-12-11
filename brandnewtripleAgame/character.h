#pragma once
#include "entity.h"

class character : public entity
{
public:
	int reload = 0;
	int weapon;
	int hp;
public:
	character();
	virtual ~character();
};

