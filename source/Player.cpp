#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture* texture)
{
    createSprite(texture);
    createMovementComponent(2.5f * 62.5f);
    setPosition(posX, posY);
}


Player::~Player()
{
}


void Player::update(const float deltaTime)
{
}