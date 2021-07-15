#include "Entity.h"


Entity::Entity()
    : pSprite(nullptr), pTexture(nullptr), pMovementComponent(nullptr)
{ 
}


Entity::~Entity()
{
    delete pSprite;
    delete pMovementComponent;
}


void Entity::createSprite(sf::Texture* const texture)
{
    pTexture = texture;
    pSprite = new sf::Sprite(*pTexture);
}


void Entity::createMovementComponent(const float maxVelocity)
{
    pMovementComponent = new MovementComponent(maxVelocity);
}


void Entity::setPosition(const float posX, const float posY)
{
    pSprite->setPosition(posX, posY);
}


void Entity::render(sf::RenderTarget* target)
{
    if (pSprite)
    {
        target->draw(*pSprite);
    }
}


void Entity::move(const float dirX, const float dirY, const float deltaTime)
{
    if (pSprite && pMovementComponent)
    {
        pMovementComponent->setVelocity(sf::Vector2f(dirX, dirY));
        pSprite->move(pMovementComponent->getVelocity() * deltaTime);
    }
}