#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <time.h>
#include "character.h"
#include "bullet.h"
#include "enemy.h"

class game
{
protected:
	sf::Clock clock;
	sf::Clock reloadClock;
	sf::Clock respawnClock;
	static game* instance;
	character player;
	std::vector <enemy> enemies;
	float delta;
	int deltaseconds;
	static bool isShooting;
	bullet playerBullet;
	bool exit = false;
	int score = 0;
public:
	sf::RenderWindow window;
	game(unsigned int width, unsigned int height, const char* title);
	virtual ~game();
	static void run();
	static void update(float delta);
	static void render();
	static void updateDelta();
	static sf::Vector2f getPlayerPos();
	static float getPlayerRotation();
};