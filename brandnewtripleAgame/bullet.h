#pragma once
#include <SFML/Graphics.hpp>
class bullet
{
public:
	sf::RectangleShape bull;
	sf::IntRect rec;
public:
	bullet();
	virtual ~bullet();
	//static void shoot();
};