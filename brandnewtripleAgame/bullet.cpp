#include "bullet.h"

sf::Texture bullet::texture;

bullet::bullet(sf::Vector2f pos) {
	texture.loadFromFile("gamedata/texture/bullet.png");
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sf::Vector2f aimDir = sf::Vector2f(sf::Mouse::getPosition()) - pos;
	sprite.setRotation(std::atan2f(aimDir.y, aimDir.x) * 180 / float(3.14));
	sf::Vector2f aimDirNorm;
	aimDir.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	aimDir.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	currVelocity.x = aimDirNorm.x * 2;
	currVelocity.y = aimDirNorm.y * 2;
	sprite.setScale(0.05, 0.05); //curr velocity 0 0, fiksi blyat'
}

bullet::~bullet(){}

void bullet::move_bullet(std::vector <bullet>& vec) {
	if (vec.size() == 0) return;
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].sprite.move(vec[i].currVelocity.x, vec[i].currVelocity.y);
	}
}