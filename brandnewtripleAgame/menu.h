#pragma once
#include "game.h"
#include "settings.h"
#include "SFML/Audio.hpp"

class menu
{
protected:
	static sf::Sprite sprite;
	static std::vector <sf::Sprite> animation;
	static std::vector <sf::Texture> animationTex;
	sf::Texture texture;
	static int animFrame;
	static sf::IntRect startr;
	static sf::IntRect settingsr;
	static sf::IntRect exitr;
	static sf::Music music_menu;
public:
	menu();
	virtual ~menu();
	static void start(game* game);
};

