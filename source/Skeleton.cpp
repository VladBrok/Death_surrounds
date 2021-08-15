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

    pAiFollow = new AiFollow(*this, player);
}


Skeleton::~Skeleton()
{
    delete pAiFollow;
}


void Skeleton::update(const float deltaTime)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    pAiFollow->update(deltaTime);


    Character::updateDamageColor();
}


void Skeleton::initAnimation()
{
    pAnimationComponent->addAnimation("MOVING_UP", texture, sprite, 0, 0, 8, 0, 64, 64, 11.f );
    pAnimationComponent->addAnimation("MOVING_LEFT", texture, sprite, 0, 1, 8, 1, 64, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_DOWN", texture, sprite, 0, 2, 8, 2, 64, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 3, 8, 3, 64, 64, 11.f);
}


void Skeleton::initDroppingItem()
{
    droppingItem = std::make_shared<Food>(Food(lootTextureSheet, sf::IntRect(1 * ONE_FOOD_TEXTURE_SIZE, 0, ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE)));
}
