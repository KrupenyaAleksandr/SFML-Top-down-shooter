#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <math.h>
#include <time.h>
#include "character.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"
#include "settings.h"

class game
{
protected:
	sf::Clock clock;
	sf::Clock reloadClock;
	sf::Clock respawnClock;
	static game* instance;
	character player;
	std::vector <enemy> enemies;
	static bool isShooting;
	std::vector <bullet> playerBullet;
	bool exit = false;
	int score = 0;
	sf::Texture mapTex;
	sf::Sprite mapSprite;
public:
	settings gamesettings;
	sound gamesound;
	sf::RenderWindow window;
	game(unsigned int width, unsigned int height, const char* title);
	virtual ~game();
	static void run();
	static void reset();
	static void update();
	static void render();
	static void save();
	static void load();
};