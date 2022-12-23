#include "entity.h"

void entity::render(sf::RenderWindow& window, sf::Sprite sprite)
{
	window.draw(sprite);
}

sf::Sprite entity::getSprite() {
	return sprite;
}