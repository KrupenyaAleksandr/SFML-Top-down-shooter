#include "enemy.h"

enemy::enemy() {
 
}

enemy::~enemy() {

}

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

void enemy::move(sf::Vector2f playerPos, float playerRotation, std::vector <enemy> enemies)
{
    // Make movement
    //sf::Vector2f playerPosition = instance->player.sprite.getPosition();
    //for (int i = 0; i < instance->zombie.size(); ++i) {
    //    float angle = atan2(instance->zombie[i].sprite.getPosition().y - instance->player.sprite.getPosition().y, instance->zombie[i].sprite.getPosition().x - instance->player.sprite.getPosition().x);
    //    angle = angle * 180 / (atan(1) * 4);
    //    sf::Vector2f newpos((cos(angle)) * 2, (sin(angle)) * 2);
    //    instance->zombie[i].sprite.setPosition(newpos);
    //}
   
    //for (int i = 0; i < enemies.size(); ++i) {
    //    sf::Vector2f direction = normalize(player.getPosition() - enemy.getPosition());
    //    sf::Vector2f thisPosition = enemies[i].sprite.getPosition();

    //    //thisPosition.x = xPos;
    //    //thisPosition.y = yPos;
    //    sf::Vector2f direction = normalize(playerPosition - thisPosition);
    //    instance->zombie[i].move(1 * direction);
    //}
}
