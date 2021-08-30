#include "precompiled.h"
#include "Skeleton.h"
#include "Food.h"
#include "constants.h"


Skeleton::Skeleton(const float posX, 
                   const float posY, 
                   const sf::Texture& textureSheet,
                   const sf::Texture& lootTextureSheet,
                   Entity& player
                   )
    : Enemy(posX, posY, textureSheet, lootTextureSheet)
{
    expForKillingMax = 12;

    createMovementComponent(80.f, 1200.f, 700.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(17.f, 15.f, 30.f, 30.f);
    createAttributeComponent(1, 7, 1, 3);

    initAnimation();
    initDroppingItem();

    aiFollow.reset(new AiFollow(*this, player));
}


void Skeleton::update(const float deltaTime)
{
    movementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    hitboxComponent->update();

    aiFollow->update(deltaTime);


    Character::updateDamageColor();
}


void Skeleton::initAnimation()
{
    animationComponent->addAnimation("MOVING_UP",    texture, sprite, 0, 0, 8, 0, 64, 64, 11.f );
    animationComponent->addAnimation("MOVING_LEFT",  texture, sprite, 0, 1, 8, 1, 64, 64, 11.f);
    animationComponent->addAnimation("MOVING_DOWN",  texture, sprite, 0, 2, 8, 2, 64, 64, 11.f);
    animationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 3, 8, 3, 64, 64, 11.f);
}


void Skeleton::initDroppingItem()
{
    sf::Vector2i itemSize(ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE);
    sf::Vector2i itemPosition(1 * ONE_FOOD_TEXTURE_SIZE, 0);

    droppingItem = std::make_shared<Food>(lootTextureSheet, sf::IntRect(itemPosition, itemSize));
}
