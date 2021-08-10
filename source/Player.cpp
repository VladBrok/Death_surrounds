#include "precompiled.h"
#include "Player.h"
#include "constants.h"


Player::Player(const float posX, 
               const float posY, 
               sf::Texture& textureSheet
               )
    : Entity(textureSheet), inventory(INVENTORY_SIZE_MAX), pActiveWeapon(nullptr)
{

    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 19.f, 28.f, 38.f);
    createAttributeComponent(1, 10, 1, 2);

    pAnimationComponent->addAnimation("IDLE", textureSheet, sprite, 0, 0, 8, 0, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_LEFT", textureSheet, sprite, 4, 1, 7, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", textureSheet, sprite, 8, 1, 11, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_UP", textureSheet, sprite, 12, 1, 15, 1, 64, 64, 9.5f );

    setPosition(posX, posY);

    initDamageTimerMax();
}


void Player::update(const float deltaTime, const sf::Vector2f& mousePosView)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    updateInventory(mousePosView);

    if (!canBeDamaged())
    {
        sprite.setColor(sf::Color::Red);
    }
    else
    {
        sprite.setColor(sf::Color::White);
    }


    // DEBUG
    //std::cout << inventory.getSize() << '\n';
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


bool Player::addItemToInventory(Item* pItem, const bool isWeapon, const bool setAsActive)
{
    assert(pItem != nullptr);
    bool isAdded = inventory.addItem(pItem);

    if (isAdded)
    {
        if (isWeapon)
        {
            Weapon* pWeapon = dynamic_cast<Weapon*>(&inventory.back());
            if (pWeapon)
            {
                pActiveWeapon = pWeapon;
            }
        }

        if (setAsActive || isWeapon)
        {
            inventory.setActiveItem(inventory.getSize() - 1);
        }
    }

    return isAdded;
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


int Player::getDamage() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getDamage() + pAttributeComponent->getDamage();  
    }
    return pAttributeComponent->getDamage();
}


float Player::getAttackRange() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getRange();
    }
    return 40.f;
}


const std::string Player::getStatsAsString() const
{
    std::stringstream stream;

    stream << "Level: " << pAttributeComponent->level << '\n'
           << "Health: " << pAttributeComponent->hp << '\n'
           << "Max Health: " << pAttributeComponent->hpMax << '\n'
           << "Exp: " << pAttributeComponent->exp << '\n'
           << "Exp for the next level: " << pAttributeComponent->expForNextLevel << "\n\n"
           << "Attack range: " << getAttackRange() << '\n'
           << "Min damage: " << (pActiveWeapon ? (pActiveWeapon->getDamageMin() + pAttributeComponent->damageMin): pAttributeComponent->damageMin) << '\n'
           << "Max damage: " << (pActiveWeapon ? (pActiveWeapon->getDamageMax() + pAttributeComponent->damageMax): pAttributeComponent->damageMax) << '\n';

    return stream.str();
}


int Player::getNumberOfItems() const
{
    return inventory.getSize();
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


void Player::setAttackStatus(const bool attacking)
{
    this->attacking = attacking;
}


bool Player::isAttacking() const
{
    return attacking;
}


bool Player::canBeDamaged() const
{
    return damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax;
}


void Player::restartDamageTimer()
{
    damageTimer.restart();
}


bool Player::canAttack() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->canAttack();
    }

    return true;
}


bool Player::isDead() const
{
    return pAttributeComponent->hp <= 0;
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


void Player::initDamageTimerMax()
{
    damageTimerMax = 350;
}