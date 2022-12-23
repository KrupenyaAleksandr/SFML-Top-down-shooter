#include "enemy.h"

sf::Texture enemy::texture;

enemy::enemy(sf::Vector2f pos) {
	texture.loadFromFile("gamedata/texture/zumbi.png");
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setPosition(pos);
	sprite.setTexture(texture);
	sprite.setScale(1, 1);
}

enemy::~enemy() {

}

void enemy::spawn(std::vector <enemy>& enemies) {
	sf::Vector2f pos;
	int cmd = rand() % 4;
	float random = rand() % 1000;
	switch (cmd) {
	case 0: {
		pos = { -50, random};
		enemies.push_back(enemy(pos));
	}
		  break;
	case 1: {
		pos = { random, -10};
		enemies.push_back(enemy(pos));
	}
		  break;
	case 2: {
		pos = { 1300, random };
		enemies.push_back(enemy(pos));
	}
		  break;
	case 3: {
		pos = { random, 1000};
		enemies.push_back(enemy(pos));
	}
		  break;
	}
}

void enemy::move(sf::Vector2f playerPos, float playerRotation, std::vector <enemy>& enemies)
{
	sf::Vector2f direction;
	for (int i = 0; i < enemies.size(); ++i) {
		direction = { playerPos.x - enemies[i].sprite.getPosition().x, playerPos.y - enemies[i].sprite.getPosition().y };
		enemies[i].sprite.setRotation(std::atan2f(direction.y, direction.x) * 180 / float(3.14));
		float hyp = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= hyp;
		direction.y /= hyp;
		sf::Vector2f tmp = enemies[i].sprite.getPosition();
		enemies[i].sprite.move(direction.x * 3, direction.y * 3);
	}
}

void enemy::enemy_shoot(std::vector <enemy>& enemies, std::vector <bullet>& bullets, int& score) {
	for (int i = 0; i < enemies.size(); ++i) {
		for (int j = 0; j < bullets.size(); ++j) {
			if (enemies[i].sprite.getGlobalBounds().intersects(bullets[j].sprite.getGlobalBounds())) {
				enemies.erase(enemies.begin() + i);
				bullets.erase(bullets.begin() + j);
				score += 1;
			}
		}
	}
}