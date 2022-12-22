#include "bullet.h"

bullet::bullet() {
	texture.loadFromFile("gamedata/texture/shoot.png");
	sprite.setTexture(texture);
	//bull.setSize(sf::Vector2f(5, 1500));
	//bull.setFillColor(sf::Color::Yellow);
}

bullet::~bullet(){}