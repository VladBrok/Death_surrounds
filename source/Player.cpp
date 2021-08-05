#include "precompiled.h"
#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet, Inventory& inventory)
    : Entity(textureSheet), inventory(inventory)
{

    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(17.f, 9.f, 30.f, 50.f);
    createAttributeComponent(1);

    pAnimationComponent->addAnimation("IDLE", textureSheet, sprite, 0, 0, 8, 0, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_LEFT", textureSheet, sprite, 4, 1, 7, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", textureSheet, sprite, 8, 1, 11, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_UP", textureSheet, sprite, 12, 1, 15, 1, 64, 64, 9.5f );

    setPosition(posX, posY);
}


void Player::update(const float deltaTime, const sf::Vector2f& mousePosView)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    updateInventory(mousePosView);
}


void Player::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const sf::Vector2f& shaderLightPosition,
                    const bool showHitbox
                    )
{
    Entity::render(target, pShader, shaderLightPosition, showHitbox);
    renderInventory(target);
}


int Player::getHP() const
{
    return pAttributeComponent->hp;
}


int Player::getHPMax() const
{
    return pAttributeComponent->hpMax;
}


int Player::getExp() const
{
    return pAttributeComponent->exp;
}


int Player::getExpForNextLevel() const
{
    return pAttributeComponent->expForNextLevel;
}


unsigned Player::getLevel() const
{
    return pAttributeComponent->level;
}


void Player::loseHp(const unsigned hp)
{
    pAttributeComponent->loseHp(hp);
}


void Player::gainHp(const unsigned hp)
{
    pAttributeComponent->gainHp(hp);
}


void Player::loseExp(const unsigned exp)
{
    pAttributeComponent->loseExp(exp);
}


void Player::gainExp(const unsigned exp)
{
    pAttributeComponent->gainExp(exp);
}


void Player::updateAnimation(const float deltaTime)
{
    try
    {
        const std::string& movementState = pMovementComponent->getMovementState();

        // Playing animations using the player's velocity as modifier for animation speed
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
        std::cout << "ERROR in Player::updateAnimation:\nthere is no animation for this type of player movement.\n";
    }
}


void Player::updateInventory(const sf::Vector2f& mousePosView)
{
    inventory.update(getCenter(), mousePosView);
}


void Player::renderInventory(sf::RenderTarget& target)
{
    inventory.render(target);
}