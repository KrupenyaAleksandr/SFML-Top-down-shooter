#pragma once
#include "entity.h"

class enemy : public entity
{
public:
	enemy();
	virtual ~enemy();
	void move(sf::Vector2f playerPos, float playerRotation, std::vector <enemy> enemies);
	sf::Vector2f normalize(const sf::Vector2f& source);
};