#pragma once
#include <SFML/Graphics.hpp>
class bullet
{
public:
	static sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f playerCenter;
	sf::Vector2f mousePos;
	sf::Vector2f currVelocity;
public:
	bullet(sf::Vector2f pos);
	static void move_bullet(std::vector <bullet>& vec);
	virtual ~bullet();
	//static void shoot();
};