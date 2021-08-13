#include "precompiled.h"
#include "Reaper.h"
#include "Food.h"
#include "constants.h"


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
    createHitboxComponent(0.f, 0.f, 39.f, 48.f);
    initAttributeComponent();

    initAnimation();
    initDroppingItem();

    pAiSpawnMinion = new AiSpawnMinion(*this, SKELETON, 5, 2);
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


    Character::updateDamageColor();
}


void Reaper::updateAnimation(const float deltaTime)
{
    try
    {
        const std::string& movementState = pMovementComponent->getMovementState();

        // Playing animations using the enemy's velocity as modifier for animation speed
        float modifier = (movementState == "MOVING_RIGHT" || movementState == "MOVING_LEFT") ? pMovementComponent->getVelocity().x: pMovementComponent->getVelocity().y;
        float modifierMax = pMovementComponent->getMaxVelocity();

        pAnimationComponent->play(
            movementState, 
            deltaTime, 
            modifier,
            modifierMax
        ); 
    }
    catch(std::out_of_range&)
    {
        //std::cout << "ERROR in Reaper::updateAnimation:\nthere is no animation for this type of enemy movement.\n";
    }
}


void Reaper::initAttributeComponent()
{
    createAttributeComponent(1, 20, 2, 4);
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
