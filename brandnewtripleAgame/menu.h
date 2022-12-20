#pragma once
#include "game.h"

class menu
{
protected:
	static sf::Sprite sprite;
	sf::Texture texture;
	static sf::IntRect startr;
	static sf::IntRect settingsr;
	static sf::IntRect exitr;
public:
	menu();
	virtual ~menu();
	static void start(game* game);
};

