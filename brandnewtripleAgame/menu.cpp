#include "menu.h"

sf::Sprite menu::sprite;

sf::IntRect menu::startr = { 297, 101, 300, 100 };
sf::IntRect menu::settingsr = { 300, 455, 300, 100 };
sf::IntRect menu::exitr = { 300, 805, 300, 100 };

menu::menu(){
	texture.loadFromFile("gamedata/texture/menu.png"); // не работает пока что
	menu::sprite.setTexture(texture);
	menu::sprite.setPosition(0, 0);
}

menu::~menu(){}

void menu::start(game* game) {
	while (game->window.isOpen()) {
		sf::Event event;
		while (game->window.pollEvent(event)) {
			game->window.draw(menu::sprite);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (menu::startr.contains(sf::Mouse::getPosition(game->window))) {
					game->run();
				}
				else if (menu::exitr.contains(sf::Mouse::getPosition(game->window))) {
						game->window.close();
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					game->window.close();
				}
			}
			else if (event.type == sf::Event::Closed) {
					game->window.close();
			}
		}
	}
}