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
    expForKillingMax = 70;

    createMovementComponent(65.f, 800.f, 500.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(0.f, 4.f, 39.f, 39.f);
    createAttributeComponent(20, 40, 2, 4);

    initAnimation();
    initDroppingItem();

    aiSpawnMinion.reset(new AiSpawnMinion(*this, SKELETON, 7, 2));
    aiFollow.reset(new AiFollow(*this, player));
}


void Reaper::update(const float deltaTime)
{
    movementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    hitboxComponent->update();

    aiSpawnMinion->update(enemySystem);
    if (utils::getDistance(getCenter(), aiFollow->getTargetEntity().getCenter()) > GRID_SIZE * 2)
    {
        aiFollow->update(deltaTime);
    }
    

    Character::updateDamageColor();
}


void Reaper::initAnimation()
{
    animationComponent->addAnimation("MOVING_DOWN",  texture, sprite, 0, 0, 3, 0, 39, 48, 11.f);
    animationComponent->addAnimation("MOVING_LEFT",  texture, sprite, 0, 1, 3, 1, 39, 48, 11.f);
    animationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 2, 3, 2, 39, 48, 11.f);
    animationComponent->addAnimation("MOVING_UP",    texture, sprite, 0, 3, 3, 3, 39, 48, 11.f);
}


void Reaper::initDroppingItem()
{
    sf::Vector2i itemSize(ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE);
    sf::Vector2i itemPosition(9 * ONE_FOOD_TEXTURE_SIZE, 0);

    droppingItem = std::make_shared<Food>(lootTextureSheet, sf::IntRect(itemPosition, itemSize));
}
