#include "game.h"

game*game::instance = NULL;
bool game::isShooting = false;

game::game(unsigned int width, unsigned int height, const char* title) 
	:window(sf::VideoMode(width, height), title, sf::Style::Close)
{
	window.setFramerateLimit(60);
	instance = this;
	this->player.sprite.setPosition(600, 500);
}

game::~game(){}

void game::reset() {
	instance->player.sprite.setPosition(600, 500);
	instance->enemies.clear();
	instance->playerBullet.clear();
	instance->score = 0;
	isShooting = false;
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
				instance->player.sprite.move(-0.5 * 3, 0);
			}
			else {
				instance->player.sprite.move(-1.f * 4, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0.5 * 3, 0);
			}
			else {
				instance->player.sprite.move(1.f * 4, 0);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, -0.5 * 3);
			}
			else {
				instance->player.sprite.move(0, -1.f * 4);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (event.type == sf::Event::MouseMoved) {
				instance->player.sprite.move(0, 0.5 * 3);
			}
			else {
				instance->player.sprite.move(0, 1.f * 4);
			}
		}

		//shoot
		sf::Time t1;
		t1 = instance->reloadClock.getElapsedTime();
		if (event.type == sf::Event::MouseButtonReleased && t1.asSeconds() >= 0.2)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				instance->gamesound.sounds_eff[0].play();
				instance->reloadClock.restart();
				isShooting = true;
				instance->playerBullet.push_back(bullet(sf::Vector2f(instance->player.sprite.getPosition()), sf::Vector2f(sf::Mouse::getPosition(instance->window))));
			}
		}
	}
}

void game::render() {
	instance->window.clear();
	instance->window.draw(instance->mapSprite);
	sf::Vector2f lookDirection = sf::Vector2f(sf::Mouse::getPosition(instance->window)) - instance->player.sprite.getPosition();
	instance->player.sprite.setRotation(std::atan2f(lookDirection.y, lookDirection.x) * 180 / float(M_PI));
	if (isShooting) {
		instance->player.shootSprite.setPosition(instance->player.sprite.getPosition());
		instance->player.shootSprite.setRotation(instance->player.sprite.getRotation());
		instance->player.render(instance->window, instance->player.shootSprite);
		isShooting = false;
	}
	else instance->player.render(instance->window, instance->player.getSprite(0));
	for (int i = 0; i < instance->playerBullet.size(); ++i) {
		instance->playerBullet[i].render(instance->window);
	}
	for (int i = 0; i < instance->enemies.size(); ++i) {
		instance->enemies[i].render(instance->window, instance->enemies[i].getSprite());
	}
	instance->window.display();
}

void game::updateDelta() {
	instance->delta = instance->clock.restart().asMilliseconds();
}

void game::run() {
	instance->exit = false;
	instance->gamesound.music[1].play();
	instance->mapTex.loadFromFile("gamedata/texture/map.png");
	instance->mapSprite.setTexture(instance->mapTex);
	while (instance->window.isOpen()) {
		sf::Time t2;
		t2 = instance->respawnClock.getElapsedTime();
		if (instance->enemies.size() < 20 && t2.asSeconds() >= 0.8) {
			enemy::spawn(instance->enemies);
			instance->respawnClock.restart();
		}
		bullet::move_bullet(instance->playerBullet);
		enemy::move(instance->player.sprite.getPosition(), 0, instance->enemies);
		bullet::bullet_outofbounds(instance->playerBullet);
		enemy::enemy_shoot(instance->enemies, instance->playerBullet, instance->score);
		if (character::collision_withenemy(instance->enemies, instance->player.sprite)) {
			instance->gamesound.sounds_eff[1].play();
			instance->reset(); 
		}
		std::cout << instance->score << std::endl;
		updateDelta();
		update(instance->delta);
		render();
		if (instance->exit) {
			instance->gamesound.music[1].stop();
			return;
		}
	}
}