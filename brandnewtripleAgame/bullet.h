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
	bullet(sf::Vector2f pos, sf::Vector2f mousePos);
	static void move_bullet(std::vector <bullet>& vec);
	static void bullet_outofbounds(std::vector <bullet>& vec);
	void render(sf::RenderWindow& window);
	virtual ~bullet();
	//static void shoot();
};

