#pragma once
#include <SFML/Graphics.hpp>
#include "sound.h"
#include <SFML/Audio.hpp>

class settings
{
public:
	static sf::Texture settingsTex;
	static sf::Sprite settingsSprite;
	static sf::Texture galochkaTex;
	static sf::Sprite galochkaSprite;
	static sf::IntRect musicr;
	static sf::IntRect soundeffr;
	static int _music;
	static int _soundeff;
public:
	settings();
	static void save_settings();
	static void load_settings();
	static void open_settings(sf::RenderWindow& window, settings& _settings, sound& _gamesound, sf::Music& menu_music);
};

