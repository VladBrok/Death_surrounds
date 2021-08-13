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
    expForKillingMax = 15;

    createMovementComponent(120.f, 1700.f, 1100.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 46.f, 26.f, 20.f);
    initAttributeComponent();

    initAnimation();
    initDroppingItem();

    pAiFollow = new AiFollow(*this, player);
}


Spider::~Spider()
{
    delete pAiFollow;
}


void Spider::update(const float deltaTime)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    pAiFollow->update(deltaTime);


    Character::updateDamageColor();
}


void Spider::updateAnimation(const float deltaTime)
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
        std::cout << "ERROR in Spider::updateAnimation:\nthere is no animation for this type of enemy movement\n";
    }
}


void Spider::initAttributeComponent()
{
    createAttributeComponent(1, 10, 2, 3);
}


void Spider::initAnimation()
{
    pAnimationComponent->addAnimation("IDLE", texture, sprite, 0, 0, 2, 0, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_DOWN", texture, sprite, 0, 0, 2, 0, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_LEFT", texture, sprite, 0, 1, 2, 1, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", texture, sprite, 0, 2, 2, 2, 60, 64, 11.f);
    pAnimationComponent->addAnimation("MOVING_UP", texture, sprite, 0, 3, 2, 3, 60, 64, 11.f );
}


void Spider::initDroppingItem()
{
    droppingItem = std::make_shared<Food>(Food(lootTextureSheet, sf::IntRect(2 * ONE_FOOD_TEXTURE_SIZE, 0, ONE_FOOD_TEXTURE_SIZE, ONE_FOOD_TEXTURE_SIZE)));
}
