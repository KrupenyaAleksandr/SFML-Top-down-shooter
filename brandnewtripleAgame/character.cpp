#include "character.h"

character::character(){
	texture.loadFromFile("gamedata/texture/handgun1.png");
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setTexture(texture);
	sprite.setScale(1.5, 1.5);
}

character::~character(){}