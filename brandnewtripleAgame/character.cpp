#include "character.h"

character::character(){
	texture.loadFromFile("gamedata/texture/handgun1.png");
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setTexture(texture);
}

character::~character(){}