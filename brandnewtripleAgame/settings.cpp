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

void settings::save_settings(settings _settings) {
	std::ofstream fout("settings.txt");
	fout << _settings._music << " " << _settings._soundeff;
	fout.close();
}

void settings::load_settings(settings& _settings) {
	std::ifstream fin("settings.txt");
	if (fin.peek() == EOF) return;
	fin >> _settings._music;
	fin >> _settings._soundeff;
	fin.close();
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
						if (_settings._soundeff == 0) {
							_settings._soundeff = 1;
							_gamesound.sounds_eff[0].setVolume(100);
							_gamesound.sounds_eff[1].setVolume(30);
						}
						else if (_settings._soundeff == 1) {
							_settings._soundeff = 0;
							_gamesound.sounds_eff[0].setVolume(0);
							_gamesound.sounds_eff[1].setVolume(0);
						}
					}
				}
			}
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					save_settings(_settings);
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