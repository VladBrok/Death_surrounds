#include "precompiled.h"
#include "Character.h"


Character::Character(const sf::Texture& texture)
    : Entity(texture), justSpawned(true)
{
}


void Character::gainHp(const int hp)
{
    pAttributeComponent->gainHp((int)hp);
}


void Character::loseHp(const int hp)
{
    pAttributeComponent->loseHp((int)hp);
}


bool Character::isDead() const
{
    return pAttributeComponent->hp <= 0;
}


int Character::getDamage() const
{
    return pAttributeComponent->getDamage();
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