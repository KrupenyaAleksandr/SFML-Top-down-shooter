#include "settings.h"

sf::IntRect settings::musicr = {765, 347, 71, 73};
sf::IntRect settings::soundeffr = { 820, 515, 72, 73 };

sf::Texture settings::settingsTex;
sf::Sprite settings::settingsSprite;
sf::Texture settings::galochkaTex;
sf::Sprite settings::galochkaSprite;
int settings::_music;
int settings::_soundeff;

settings::settings() {
	settingsTex.loadFromFile("gamedata/texture/settings.png");
	settingsSprite.setTexture(settingsTex);
	galochkaTex.loadFromFile("gamedata/texture/galochka.png");
	galochkaSprite.setTexture(galochkaTex);
}

void settings::open_settings(sf::RenderWindow& window, settings& _settings, sound& _gamesound, sf::Music& menu_music) {
	while (window.isOpen()) {
		sf::Event event;
		window.draw(_settings.settingsSprite);
		if (_music == 1) {
			_settings.galochkaSprite.setPosition(770, 300);
			window.draw(_settings.galochkaSprite);
		}
		if (_soundeff == 1) {
			_settings.galochkaSprite.setPosition(825, 470);
			window.draw(_settings.galochkaSprite);
		}
		while (window.pollEvent(event)) {
			window.draw(_settings.settingsSprite);
			if (_settings._music == 1) {
				_settings.galochkaSprite.setPosition(770, 300);
				window.draw(_settings.galochkaSprite);
			}
			if (_settings._soundeff == 1) {
				_settings.galochkaSprite.setPosition(825, 470);
				window.draw(_settings.galochkaSprite);
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (_settings.musicr.contains(sf::Mouse::getPosition(window))) {
						if (_settings._music == 0) {
							_settings._music = 1;
							menu_music.setVolume(15);
							_gamesound.music[1].setVolume(2);
						}
						else if (_settings._music == 1) {
							_settings._music = 0;
							menu_music.setVolume(0);
							_gamesound.music[1].setVolume(0);
						}
					}
					else if (_settings.soundeffr.contains(sf::Mouse::getPosition(window))) {
						if (_settings._soundeff == 0) _settings._soundeff = 1;
						else if (_settings._soundeff == 1) _settings._soundeff = 0;
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					return;
				}
			}
			else if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.display();
	}
}

//void settings::open_settings(game* game, settings _settings) {
//	while (game->window.isOpen()) {
//		sf::Event event;
//		game->window.draw(_settings.settingsSprite);
//		if (_settings._music == 1) {
//			_settings.galochkaSprite.setPosition(825, 500);
//			game->window.draw(_settings.galochkaSprite);
//		}
//		if (_settings._soundeff == 1) {
//			_settings.galochkaSprite.setPosition(770, 330);
//			game->window.draw(_settings.galochkaSprite);
//		}
//		while (game->window.pollEvent(event)) {
//			game->window.draw(_settings.settingsSprite);
//			if (_settings._music == 1) {
//				_settings.galochkaSprite.setPosition(825, 500);
//				game->window.draw(_settings.galochkaSprite);
//			}
//			if (_settings._soundeff == 1) {
//				_settings.galochkaSprite.setPosition(770, 330);
//				game->window.draw(_settings.galochkaSprite);
//			}
//			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//				if (_settings.musicr.contains(sf::Mouse::getPosition(game->window))) {
//					_settings._music = 0;
//				}
//				else if (_settings.soundeffr.contains(sf::Mouse::getPosition(game->window))) {
//					_settings._soundeff = 0;
//				}
//			}
//			else if (event.type == sf::Event::KeyPressed) {
//				if (event.key.code == sf::Keyboard::Escape) {
//					return;
//				}
//			}
//			else if (event.type == sf::Event::Closed) {
//				game->window.close();
//			}
//		}
//		game->window.display();
//	}
//}