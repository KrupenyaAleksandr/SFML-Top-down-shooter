#pragma once
#include "entity.h"
#include "enemy.h"

class character : public entity
{
public:
	sf::Texture shootTex;
	sf::Sprite shootSprite;
public:
	character();
	static bool collision_withenemy(std::vector <enemy>& enemies, sf::Sprite& sprite);
	virtual sf::Sprite getSprite(int cmd);
	virtual ~character();
};

