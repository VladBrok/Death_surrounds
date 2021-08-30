#include "precompiled.h"
#include "Spider.h"
#include "Food.h"
#include "constants.h"


Spider::Spider(const float posX, 
               const float posY, 
               const sf::Texture& textureSheet,
               const sf::Texture& lootTextureSheet,
               Entity& player
               )
    : Enemy(posX, posY, textureSheet, lootTextureSheet)
{
    expForKillingMax = 25;

    createMovementComponent(240.f, 1700.f, 1100.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 46.f, 26.f, 20.f);
    createAttributeComponent(5, 10, 2, 3);

    initAnimation();
    initDroppingItem();

    aiFollow = new AiFollow(*this, player);
}


void Spider::update(const float deltaTime)
{
    movementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    hitboxComponent->update();

    aiFollow->update(deltaTime);


    Character::updateDamageColor();
}


void Spider::initAnimation()
{
    animationComponent->addAnimation("IDLE",         texture, sprite, 0, 0, 2, 0, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_DOWN",  texture, sprite, 0, 0, 2, 0, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_LEFT",  texture, sprite, 0, 1, 2, 1, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 2, 2, 2, 60, 64, 11.f);
    animationComponent->addAnimation("MOVING_UP",    texture, sprite, 0, 3, 2, 3, 60, 64, 11.f );
}


void Spider::initDroppingItem()
{
    sf::Vector2i itemSize(ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE);
    sf::Vector2i itemPosition(2 * ONE_FOOD_TEXTURE_SIZE, 0);

    droppingItem = std::make_shared<Food>(lootTextureSheet, sf::IntRect(itemPosition, itemSize));
}
