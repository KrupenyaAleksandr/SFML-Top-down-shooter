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
		if (event.type == sf::Event::MouseButtonReleased && t1.asSeconds() >= 1)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				instance->playerBullet.push_back(sf::Vector2f(instance->player.sprite.getPosition()));
			}
		}
	}
}

void game::render() {
	instance->window.clear();
	sf::Vector2f lookDirection = sf::Vector2f(sf::Mouse::getPosition(instance->window)) - instance->player.sprite.getPosition();
	instance->player.sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / float(M_PI));
	instance->player.render(instance->window);
	for (int i = 0; i < instance->playerBullet.size(); ++i) {
		instance->window.draw(instance->playerBullet[i].sprite);
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
		bullet::move_bullet(instance->playerBullet);
		enemy::move(instance->player.sprite.getPosition(), 0, instance->enemies);
		updateDelta();
		update(instance->delta);
		render();
		if (instance->exit) {
			return;
		}
	}
}