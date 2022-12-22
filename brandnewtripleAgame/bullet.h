#pragma once
#include <SFML/Graphics.hpp>
class bullet
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape bull;
	sf::IntRect rec;
public:
	bullet();
	virtual ~bullet();
	//static void shoot();
};