#include "bullet.h"

bullet::bullet() {
	bull.setSize(sf::Vector2f(3, 2000));
	//bull.setOrigin(0, 0);
	bull.setFillColor(sf::Color::Yellow);
}

bullet::~bullet(){}