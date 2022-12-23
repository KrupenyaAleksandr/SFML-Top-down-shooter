#include "bullet.h"

sf::Texture bullet::texture;

bullet::bullet(sf::Vector2f pos, sf::Vector2f mousePos) {
	texture.loadFromFile("gamedata/texture/bullet.png");
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setTexture(texture);
	sf::Vector2f aimDir = mousePos - pos;
	sprite.setRotation(std::atan2f(aimDir.y, aimDir.x) * 180 / float(3.14) - 180);
	sf::Vector2f aimDirNorm;
	aimDirNorm.x = aimDir.x / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	aimDirNorm.y = aimDir.y / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	currVelocity.x = aimDirNorm.x * 70;
	currVelocity.y = aimDirNorm.y * 70;
	sprite.setScale(0.03, 0.03);
	sprite.setPosition(pos.x + currVelocity.x * 1.5, pos.y + currVelocity.y * 1.5);
	//curr velocity 0 0, fiksi blyat'
}

bullet::~bullet(){}

void bullet::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void bullet::move_bullet(std::vector <bullet>& vec) {
	if (vec.size() == 0) return;
	for (int i = 0; i < vec.size(); ++i) {
		vec[i].sprite.move(vec[i].currVelocity.x, vec[i].currVelocity.y);
	}
}

void bullet::bullet_outofbounds(std::vector <bullet>& vec) {
	if (vec.size() == 0) return;
	for (int i = 0; i < vec.size(); ++i) {
		int x = vec[i].sprite.getPosition().x;
		int y = vec[i].sprite.getPosition().y;
		if (x < 0 || y < 0 || x > 1200 || y > 1000) vec.erase(vec.begin() + i);
	}
}