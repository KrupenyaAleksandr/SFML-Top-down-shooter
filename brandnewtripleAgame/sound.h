#pragma once
#include <SFML/Audio.hpp>

class sound {
public:
	static std::vector <sf::SoundBuffer> buffer;
	static std::vector <sf::Sound> sounds_eff;
	static std::vector <sf::Music> music;
public:
	sound();
};