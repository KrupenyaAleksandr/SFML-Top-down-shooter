#pragma once
#include "entity.h"

class character : public entity
{
public:
	sf::Texture shootTex;
	sf::Sprite shootSprite;
public:
	character();
	virtual sf::Sprite getSprite(int cmd);
	virtual ~character();
};

