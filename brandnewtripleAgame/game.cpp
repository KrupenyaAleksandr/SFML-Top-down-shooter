#include "game.h"

game* game::instance = NULL;
bool game::isShooting = false;

game::game(unsigned int width, unsigned int height, const char* title) 
	:window(sf::VideoMode(width, height), title, sf::Style::Close)
{
	window.setFramerateLimit(60);
	instance = this;
}

game::~game(){}

void game::update(float delta) {
	sf::Event event;
	auto t1 = std::chrono::high_resolution_clock::now();
	while (instance->window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			instance->window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				instance->window.close();
			}
		}

		//playermovement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(-0.5 * (delta / 8), 0);
			}
			else {
				instance->player.sprite.move(-1 * (delta / 8), 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0.5 * (delta / 8), 0);
			}
			else {
				instance->player.sprite.move(1 * (delta / 8), 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, -0.5 * (delta / 8));
			}
			else {
				instance->player.sprite.move(0, -1 * (delta / 8));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, 0.5 * (delta / 8));
			}
			else {
				instance->player.sprite.move(0, 1 * (delta / 8));
			}
		}

		//shoot
		std::cout << instance->player.reload << std::endl;
		sf::Time t1;
		t1 = instance->reloadClock.getElapsedTime();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && t1.asSeconds() >= 0.3) {
			isShooting = true;
			std::cout << "SHOT" << std::endl;
			instance->reloadClock.restart();
		}
	}
}

void game::render() {
	instance->window.clear();
	sf::Vector2f lookDirection = sf::Vector2f(sf::Mouse::getPosition(instance->window)) - instance->player.sprite.getPosition();
	instance->player.sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / float(M_PI));
	instance->player.render(instance->window);
	if (isShooting) {
		instance->playerBullet.bull.setPosition(instance->player.sprite.getPosition());
		instance->playerBullet.bull.setRotation(instance->player.sprite.getRotation() - 90);
		instance->window.draw(instance->playerBullet.bull);
		isShooting = false;
	}
	instance->window.display();
}

void game::updateDelta() {
	instance->delta = instance->clock.restart().asMilliseconds();
}

void game::run() {
	//auto t1 = std::chrono::high_resolution_clock::now();
	while (instance->window.isOpen()) {
		//auto t2 = std::chrono::high_resolution_clock::now();
		//std::chrono::duration<float> dt = t2 - t1;
		//t1 = t2;
		//instance->deltaseconds = dt.count();
		updateDelta();
		update(instance->delta);
		render();
	}
}