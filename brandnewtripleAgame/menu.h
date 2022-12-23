#pragma once
#include "game.h"

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
public:
	menu();
	virtual ~menu();
	static void start(game* game);
};

