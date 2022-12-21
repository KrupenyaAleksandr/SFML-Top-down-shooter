#include "menu.h"

sf::Sprite menu::sprite;

sf::IntRect menu::startr = { 300, 105, 600, 140 };
sf::IntRect menu::settingsr = { 300, 455, 600, 140 };
sf::IntRect menu::exitr = { 300, 805, 600, 140 };

menu::menu(){
	texture.loadFromFile("gamedata/texture/menu.png");
	menu::sprite.setTexture(texture);
}

menu::~menu(){}

void menu::start(game* game) {
	while (game->window.isOpen()) {
		sf::Event event;
		game->window.draw(menu::sprite);
		game->window.display();
		while (game->window.pollEvent(event)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				std::cout << sf::Mouse::getPosition(game->window).x << " " << sf::Mouse::getPosition(game->window).y << std::endl;
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