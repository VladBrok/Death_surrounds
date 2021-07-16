#include "Player.h"


Player::Player(const float posX, const float posY, const sf::Texture& texture)
    : Entity(texture)
{
    createMovementComponent(160.f, 1400.f, 1000.f);
    setPosition(posX, posY);
}


Player::~Player()
{
}
