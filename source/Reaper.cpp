#include "precompiled.h"
#include "Reaper.h"
#include "Food.h"
#include "constants.h"
#include "Utils.h"


Reaper::Reaper(const float posX, 
               const float posY, 
               const sf::Texture& textureSheet,
               const sf::Texture& lootTextureSheet,
               Entity& player,
               EnemySystem& enemySystem
               )
    : Enemy(posX, posY, textureSheet, lootTextureSheet),
      enemySystem(enemySystem)
{
    expForKillingMax = 50;

    createMovementComponent(65.f, 800.f, 500.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(0.f, 4.f, 39.f, 39.f);
    createAttributeComponent(5, 20, 2, 4);

    initAnimation();
    initDroppingItem();

    pAiSpawnMinion = new AiSpawnMinion(*this, SKELETON, 7, 2);
    pAiFollow = new AiFollow(*this, player);
}


Reaper::~Reaper()
{
    delete pAiSpawnMinion;
}


void Reaper::update(const float deltaTime)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    pAiSpawnMinion->update(enemySystem);
    if (utils::getDistance(getCenter(), pAiFollow->getTargetEntity().getCenter()) > GRID_SIZE * 2)
    {
        pAiFollow->update(deltaTime);
    }
    

    Character::updateDamageColor();
}


void Reaper::initAnimation()
{
    pAnimationComponent->addAnimation("MOVING_DOWN",  texture, sprite, 0, 0, 3, 0, 39, 48, 11.f);
    pAnimationComponent->addAnimation("MOVING_LEFT",  texture, sprite, 0, 1, 3, 1, 39, 48, 11.f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 2, 3, 2, 39, 48, 11.f);
    pAnimationComponent->addAnimation("MOVING_UP",    texture, sprite, 0, 3, 3, 3, 39, 48, 11.f);
}


void Reaper::initDroppingItem()
{
    droppingItem = std::make_shared<Food>(Food(lootTextureSheet, sf::IntRect(9 * ONE_FOOD_TEXTURE_SIZE, 0, ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE)));
}
