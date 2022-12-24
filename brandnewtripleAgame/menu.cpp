#include "menu.h"
#include <string>

sf::Sprite menu::sprite;
std::vector <sf::Sprite> menu::animation(151);
std::vector <sf::Texture> menu::animationTex(151);
sf::Music menu::music_menu;
int menu::animFrame = 0;

sf::IntRect menu::startr = { 438, 337, 320, 72 };
sf::IntRect menu::settingsr = { 320, 470, 544, 72 };
sf::IntRect menu::exitr = { 446, 621, 270, 72 };

menu::menu(){
	sf::IntRect tmpRect = { 160, 150, 300, 80 };
	for (int i = 0; i < 152; ++i) {
		std::string num = std::to_string(i);
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
	music_menu.openFromFile("gamedata/sound/Modulogeek-Around.wav");
	music_menu.setLoop(true);
	music_menu.setVolume(15);
}

menu::~menu(){}

void menu::start(game* game) {
	settings::load_settings(game->gamesettings);
	if (game->gamesettings._music == 1) {
		music_menu.setVolume(15);
		game->gamesound.music[1].setVolume(2);
	}
	else if (game->gamesettings._music == 0) {
		music_menu.setVolume(0);
		game->gamesound.music[1].setVolume(0);
	}
	if (game->gamesettings._soundeff == 1) {
		game->gamesound.sounds_eff[0].setVolume(100);
		game->gamesound.sounds_eff[1].setVolume(30);
	}
	else if (game->gamesettings._soundeff == 0) {
		game->gamesound.sounds_eff[0].setVolume(0);
		game->gamesound.sounds_eff[1].setVolume(0);
	}
	music_menu.play();
	while (game->window.isOpen()) {
		sf::Event event;
		game->window.draw(menu::sprite);
		game->window.draw(menu::animation[animFrame]);
		while (game->window.pollEvent(event)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				std::cout << sf::Mouse::getPosition(game->window).x << " " << sf::Mouse::getPosition(game->window).y << std::endl;
				if (menu::startr.contains(sf::Mouse::getPosition(game->window))) {
					music_menu.stop();
					game->run();
					music_menu.play();
				}
				else if (menu::settingsr.contains(sf::Mouse::getPosition(game->window))) {
					game->gamesettings.open_settings(game->window, game->gamesettings, game->gamesound, music_menu);
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