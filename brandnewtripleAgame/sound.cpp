#include "sound.h"

std::vector <sf::SoundBuffer> sound::buffer(4);
std::vector <sf::Sound> sound::sounds_eff(2);
std::vector <sf::Music> sound::music(2);

sound::sound() {
	buffer[0].loadFromFile("gamedata/sound/silencer.wav");
	buffer[1].loadFromFile("gamedata/sound/hit.wav");
	buffer[2].loadFromFile("gamedata/sound/Modulogeek-Around.wav");
	buffer[3].loadFromFile("gamedata/sound/Carpenter-Brut-Turbo-Killer.wav");
	sounds_eff[0].setBuffer(buffer[0]);
	sounds_eff[1].setBuffer(buffer[1]);
	sounds_eff[1].setVolume(30);
	music[0].openFromFile("gamedata/sound/Modulogeek-Around.wav");
	music[0].setLoop(true);
	music[1].openFromFile("gamedata/sound/Carpenter-Brut-Turbo-Killer.wav");
	music[1].setLoop(true);
	music[1].setVolume(5);
}