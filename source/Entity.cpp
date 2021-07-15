#include "Entity.h"


Entity::Entity()
    : movementSpeed(2.5f * 62.5f), entityShape(sf::Vector2f(50.f, 50.f))
{ 
}


Entity::~Entity()
{
}


void Entity::update()
{
}


void Entity::render(sf::RenderTarget* target)
{
    target->draw(entityShape);
}


void Entity::move(const float dirX, const float dirY, const float deltaTime)
{
    entityShape.move(dirX * movementSpeed * deltaTime, dirY * movementSpeed * deltaTime);
}