#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <time.h>
#include "character.h"
#include "bullet.h"

class game
{
protected:
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Clock reloadClock;
	static game* instance;
	character player;
	float delta;
	int deltaseconds;
	static bool isShooting;
	bullet playerBullet;
public:
	game(unsigned int width, unsigned int height, const char* title);
	virtual ~game();
	static void run();
	static void update(float delta);
	static void render();
	static void updateDelta();
};