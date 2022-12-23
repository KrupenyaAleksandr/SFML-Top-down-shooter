#include "character.h"



character::character(){
	shootTex.loadFromFile("gamedata/texture/handgun2.png");
	texture.loadFromFile("gamedata/texture/handgun1.png");
	shootSprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	shootSprite.setTexture(shootTex);
	shootSprite.setScale(2, 2);
	sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.f);
	sprite.setTexture(texture);
	sprite.setScale(2, 2);
}

character::~character(){}

sf::Sprite character::getSprite(int cmd) {
	if (cmd == 1) return shootSprite;
	return sprite;
}