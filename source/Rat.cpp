#include "precompiled.h"
#include "Rat.h"
#include "Food.h"
#include "constants.h"


Rat::Rat(const float posX, 
         const float posY, 
         const sf::Texture& textureSheet,
         const sf::Texture& lootTextureSheet,
         Entity& player
         )
    : Enemy(posX, posY, textureSheet, lootTextureSheet)
{
    expForKillingMax = 10;

    createMovementComponent(100.f, 1400.f, 900.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 44.f, 20.f, 20.f);
    createAttributeComponent(1, 8, 1, 1);

    initAnimation();
    initDroppingItem();

    aiFollow.reset(new AiFollow(*this, player));
}


void Rat::update(const float deltaTime)
{
    movementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    hitboxComponent->update();

    aiFollow->update(deltaTime);


    Character::updateDamageColor();
}


void Rat::initAnimation()
{
    animationComponent->addAnimation("MOVING_DOWN",  texture, sprite, 0, 0, 3, 0, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_LEFT",  texture, sprite, 0, 1, 3, 1, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 2, 3, 2, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_UP",    texture, sprite, 0, 3, 3, 3, 60, 64, 11.f );
}


void Rat::initDroppingItem()
{
    sf::Vector2i itemSize(ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE);
    sf::Vector2i itemPosition(0 * ONE_FOOD_TEXTURE_SIZE, 0);

    droppingItem = std::make_shared<Food>(lootTextureSheet, sf::IntRect(itemPosition, itemSize));
}
