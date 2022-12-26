#include "game.h"

game*game::instance = NULL;
bool game::isShooting = false;

game::game(unsigned int width, unsigned int height, const char* title) 
	:window(sf::VideoMode(width, height), title, sf::Style::Close)
{
	window.setFramerateLimit(60);
	instance = this;
	this->player.sprite.setPosition(600, 500);
	sf::Texture tex;
	sf::Sprite spr;
	tex.loadFromFile("gamedata/texture/loading.png");
	spr.setTexture(tex);
	window.draw(spr);
	window.display();
}

game::~game(){}

void game::save() {
	std::ofstream fout("save.txt");
	fout << instance->player.sprite.getPosition().x << " " << instance->player.sprite.getPosition().y << std::endl;
	fout << instance->score << std::endl;
	fout << instance->enemies.size() << std::endl;
	for (int i = 0; i < instance->enemies.size(); ++i) {
		fout << instance->enemies[i].sprite.getPosition().x << " " << instance->enemies[i].sprite.getPosition().y << std::endl;
	}
	fout.close();
}

void game::load() {
	std::ifstream fin("save.txt");
	if (fin.peek() == EOF) return;
	sf::Vector2f tmp;
	int count;
	fin >> tmp.x >> tmp.y;
	instance->player.sprite.setPosition(tmp);
	fin >> count;
	instance->score = count;
	fin >> count;
	for (int i = 0; i < count; ++i) {
		fin >> tmp.x >> tmp.y;
		instance->enemies.push_back(enemy(tmp));
	}
}

void game::reset() {
	instance->player.sprite.setPosition(600, 500);
	instance->enemies.clear();
	instance->playerBullet.clear();
	instance->score = 0;
	isShooting = false;
}

void game::update() {
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

		//shoot
		sf::Time t1;
		t1 = instance->reloadClock.getElapsedTime();
		if (event.type == sf::Event::MouseButtonReleased && t1.asSeconds() >= 0.3)
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
	if (!isShooting) {
		instance->player.render(instance->window, instance->player.sprite);
	}
	else {
		instance->player.shootSprite.setPosition(instance->player.sprite.getPosition());
		instance->player.shootSprite.setRotation(instance->player.sprite.getRotation());
		instance->player.render(instance->window, instance->player.shootSprite);
		isShooting = false;
	}
	for (int i = 0; i < instance->playerBullet.size(); ++i) {
		instance->playerBullet[i].render(instance->window);
	}
	for (int i = 0; i < instance->enemies.size(); ++i) {
		instance->enemies[i].render(instance->window, instance->enemies[i].getSprite());
	}
	instance->window.draw(instance->_score);
	instance->window.display();
}

void game::run() {
	instance->font.loadFromFile("gamedata/justice.ttf");
	instance->_score.setFont(instance->font);
	instance->_score.setPosition(15, 15);
	instance->_score.setFillColor(sf::Color::Magenta);
	instance->_score.setCharacterSize(100);
	std::string score_str;
	load();
	instance->exit = false;
	instance->gamesound.music[1].setPlayingOffset(sf::seconds(41.f));
	instance->gamesound.music[1].play();
	instance->mapTex.loadFromFile("gamedata/texture/map.png");
	instance->mapSprite.setTexture(instance->mapTex);
	while (instance->window.isOpen()) {
		score_str = std::to_string(instance->score);
		instance->_score.setString(score_str);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			instance->player.sprite.move(0.8 * 4, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			instance->player.sprite.move(-0.8 * 4, 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			instance->player.sprite.move(0, 0.8 * 4);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			instance->player.sprite.move(0, -0.8 * 4);
		}
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
			enemy::speed = 7;
		}
		update();
		render();
		if (instance->exit) {
			instance->gamesound.music[1].stop();
			save();
			instance->enemies.clear();
			return;
		}
	}
}