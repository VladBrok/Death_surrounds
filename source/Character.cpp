#include "precompiled.h"
#include "Character.h"


Character::Character(const sf::Texture& texture)
    : Entity(texture), justSpawned(true)
{
}


void Character::gainHp(const int hp)
{
    attributeComponent->gainHp((int)hp);
}


void Character::loseHp(const int hp)
{
    attributeComponent->loseHp((int)hp);
}


bool Character::isDead() const
{
    return attributeComponent->getHp() <= 0;
}


int Character::getDamage() const
{
    return attributeComponent->getDamage();
}


bool Character::canBeDamaged() const
{
    return damageTimer.getElapsedTime().asMilliseconds() >= damageTimerMax;
}


void Character::restartDamageTimer()
{
    damageTimer.restart();
}


bool Character::canAttack() const
{
    return attackTimer.getElapsedTime().asMilliseconds() >= attackTimerMax;
}


void Character::restartAttackTimer()
{
    attackTimer.restart();
}


void Character::updateDamageColor()
{
    if (!canBeDamaged() && !justSpawned)
    {
        sprite.setColor(sf::Color::Red);
    }
    else if (canBeDamaged())
    {
        sprite.setColor(sf::Color::White);
        justSpawned = false;
    }
}


void Character::updateAnimation(const float deltaTime)
{
    try
    {
        const std::string& movementState = movementComponent->getMovementState();

        // Playing animations using the character's velocity as modifier for animation speed
        float modifier = (movementState == "MOVING_RIGHT" || movementState == "MOVING_LEFT") 
                          ? movementComponent->getVelocity().x
                          : movementComponent->getVelocity().y;

        float modifierMax = movementComponent->getMaxVelocity();

        animationComponent->play(
            movementState, 
            deltaTime, 
            modifier,
            modifierMax
        ); 
    }
    catch(std::out_of_range&)
    {
        std::cout << "ERROR in Character::updateAnimation:\nthere is no animation for this type of character movement.\n";
    }
}