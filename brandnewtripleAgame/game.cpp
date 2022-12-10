#include "game.h"

game* game::instance = NULL;

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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			instance->player.sprite.move(-1 * (delta / 8), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			instance->player.sprite.move(1 * (delta / 8), 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			instance->player.sprite.move(0, -1 * (delta / 8));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			instance->player.sprite.move(0, 1 * (delta / 8));
	}
}

void game::render() {
	instance->window.clear();
	sf::Vector2f lookDirection = sf::Vector2f(sf::Mouse::getPosition(instance->window)) - instance->player.sprite.getPosition();
	instance->player.sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / float(M_PI));
	instance->player.render(instance->window);
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
		//instance->delta = dt.count();
		updateDelta();
		update(instance->delta);
		render();
	}
}