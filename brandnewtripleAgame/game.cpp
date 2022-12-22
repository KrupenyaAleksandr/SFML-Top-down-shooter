#include "game.h"

game*game::instance = NULL;
bool game::isShooting = false;

game::game(unsigned int width, unsigned int height, const char* title) 
	:window(sf::VideoMode(width, height), title, sf::Style::Close)
{
	window.setFramerateLimit(60);
	instance = this;
	this->player.sprite.setPosition(this->window.getSize().x / 2, this->window.getSize().y / 2);
}

game::~game(){}

sf::Vector2f game::getPlayerPos() {
	return instance->player.sprite.getPosition();
}

float game::getPlayerRotation() {
	return instance->player.sprite.getRotation();
}

void game::update(float delta) {
	sf::Event event;
	while (instance->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			instance->window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				instance->exit = true;
				return;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { 
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(-0.5, 0);
			}
			else {
				instance->player.sprite.move(-1.f, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0.5, 0);
			}
			else {
				instance->player.sprite.move(1.f , 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, -0.5);
			}
			else {
				instance->player.sprite.move(0, -1.f);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, 0.5);
			}
			else {
				instance->player.sprite.move(0, 1.f);
			}
		}

		//shoot
		sf::Time t1;
		t1 = instance->reloadClock.getElapsedTime();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && t1.asSeconds() >= 1) {
			if (sf::Event::MouseButtonReleased) {
				isShooting = true;
				instance->reloadClock.restart();
			}
		}
	}
}

void game::render() {
	instance->window.clear();
	sf::Vector2f lookDirection = sf::Vector2f(sf::Mouse::getPosition(instance->window)) - instance->player.sprite.getPosition();
	instance->player.sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / float(M_PI));
	instance->player.render(instance->window);
	if (isShooting) {
		std::cout << "SHOOT" << std::endl;
		instance->playerBullet.sprite.setPosition(instance->player.sprite.getPosition());
		instance->playerBullet.sprite.setRotation(instance->player.sprite.getRotation() - 90);
		instance->window.draw(instance->playerBullet.bull);
		for (int i = 0; i < instance->enemies.size(); ++i) {
			//std::cout << "Count: " << instance->playerBullet.bull.getPointCount() << std::endl;
				//if (instance->enemies[i].sprite.getGlobalBounds().intersects(instance->playerBullet.sprite.getGlobalBounds())) {
				//if (instance->playerBullet.sprite.getGlobalBounds().intersects(instance->enemies[i].sprite.getOrigin()))
					instance->score += 1;
					instance->enemies.erase(instance->enemies.begin() + i);
					break;
				}
		}
		instance->window.draw(instance->playerBullet.sprite);
		isShooting = false;
	}
	for (int i = 0; i < instance->enemies.size(); ++i) {
		instance->enemies[i].render(instance->window);
	}
	instance->window.display();
}

void game::updateDelta() {
	instance->delta = instance->clock.restart().asMilliseconds();
}

void game::run() {
	instance->exit = false;
	while (instance->window.isOpen()) {
		sf::Time t2;
		t2 = instance->respawnClock.getElapsedTime();
		if (instance->enemies.size() < 20 && t2.asSeconds() >= 1) {
			enemy::spawn(instance->enemies);
			std::cout << instance->enemies.size() << std::endl;
			instance->respawnClock.restart();
		}
		enemy::move(instance->player.sprite.getPosition(), 0, instance->enemies);
		updateDelta();
		update(instance->delta);
		render();
		if (instance->exit) {
			return;
		}
	}
}