#include "menu.h"
#include <string>

sf::Sprite menu::sprite;
std::vector <sf::Sprite> menu::animation(151);
std::vector <sf::Texture> menu::animationTex(151);
int menu::animFrame = 0;

sf::IntRect menu::startr = { 438, 337, 320, 72 };
sf::IntRect menu::settingsr = { 320, 470, 544, 72 };
sf::IntRect menu::exitr = { 446, 621, 270, 72 };

menu::menu(){
	sf::IntRect tmpRect = { 160, 150, 300, 80 };
	for (int i = 0; i < 152; ++i) {
		std::string num = std::to_string(i);
		//animation.push_back(sprite);
		//animationTex.push_back(texture);
		if (i < 10) {
			std::string tmp = "gamedata/animationmenu/frame_00" + num + "_delay-0.01s.png";
			animationTex[i].loadFromFile(tmp);
			animation[i].setTexture(animationTex[i]);
			animation[i].setTextureRect(tmpRect);
			animation[i].setPosition(150, 50);
			animation[i].setScale(3, 3);
		}
		if (i > 9 && i < 100) {
			std::string tmp = "gamedata/animationmenu/frame_0" + num + "_delay-0.01s.png";
			animationTex[i].loadFromFile(tmp);
			animation[i].setTexture(animationTex[i]);
			animation[i].setTextureRect(tmpRect);
			animation[i].setPosition(150, 50);
			animation[i].setScale(3, 3);
		}
		if (i > 99 && i < 151) {
			std::string tmp = "gamedata/animationmenu/frame_" + num + "_delay-0.01s.png";
			animationTex[i].loadFromFile(tmp);
			animation[i].setTexture(animationTex[i]);
			animation[i].setTextureRect(tmpRect);
			animation[i].setPosition(150, 50);
			animation[i].setScale(3, 3);
		}
		texture.loadFromFile("gamedata/texture/menu.png");
		menu::sprite.setTexture(texture);
	}
}

menu::~menu(){}

void menu::start(game* game) {
	while (game->window.isOpen()) {
		sf::Event event;
		game->window.draw(menu::sprite);
		game->window.draw(menu::animation[animFrame]);
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
		if (animFrame == 150) animFrame = 0;
		animFrame++;
		game->window.display();
	}
}