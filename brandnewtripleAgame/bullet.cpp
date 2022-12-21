#include "bullet.h"

bullet::bullet() {
	bull.setSize(sf::Vector2f(5, 1500));
	bull.setFillColor(sf::Color::Yellow);
}

bullet::~bullet(){}