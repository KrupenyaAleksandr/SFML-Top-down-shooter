#pragma once
#include <SFML/Graphics.hpp>

class entity
{
public:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f pos;
public:
	entity() {}
	void render(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}
};
