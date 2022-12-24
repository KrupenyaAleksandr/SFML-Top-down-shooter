#pragma once
#include "entity.h"
#include "bullet.h"

class enemy : public entity
{
public:
	static sf::Texture texture;
	static double speed;
public:
	enemy(sf::Vector2f pos);
	virtual ~enemy();
	static void spawn(std::vector <enemy>& enemies);
	static void move(sf::Vector2f playerPos, float playerRotation, std::vector <enemy>& enemies);
	static void enemy_shoot(std::vector <enemy>& enemies, std::vector <bullet>& bullets, int& score);
};