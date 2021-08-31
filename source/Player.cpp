#include "precompiled.h"
#include "Player.h"
#include "Food.h"


Player::Player(const float posX, 
               const float posY, 
               const sf::Texture& textureSheet,
               const sf::Texture& inventoryPanelTexture,
               const sf::RenderWindow& window
               )
    : Character(textureSheet), 
      inventory(window, inventoryPanelTexture), 
      pActiveWeapon(nullptr),
      deathAnimationDone(false)
{

    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 25.f, 28.f, 28.f);
    createAttributeComponent(1, 10, 1, 2);

    animationComponent->addAnimation("IS_DEAD",      textureSheet, sprite,  0, 1,  6, 1, 146, 252, 20.0f);
    animationComponent->addAnimation("IDLE",         textureSheet, sprite,  0, 0,  8, 0,  64,  64,  9.5f);
    animationComponent->addAnimation("MOVING_DOWN",  textureSheet, sprite,  0, 1,  3, 1,  64,  64,  9.5f);
    animationComponent->addAnimation("MOVING_LEFT",  textureSheet, sprite,  4, 1,  7, 1,  64,  64,  9.5f);
    animationComponent->addAnimation("MOVING_RIGHT", textureSheet, sprite,  8, 1, 11, 1,  64,  64,  9.5f);
    animationComponent->addAnimation("MOVING_UP",    textureSheet, sprite, 12, 1, 15, 1,  64,  64,  9.5f );
    
    setPosition(posX, posY);

    initTimers();
}


void Player::update(const float deltaTime, 
                    const sf::Vector2f& mousePosView, 
                    const sf::Vector2i& mousePosWindow,
                    TextTagSystem& textTagSystem
                    )
{
    if (!isDead())
    {
        movementComponent->updateMovement(deltaTime);
        updateAnimation(deltaTime);
        hitboxComponent->update();
        inventory.update(getCenter(), mousePosView, mousePosWindow, textTagSystem);
    
        if (inventory.getActiveItem())
        {
            // Setting the player's weapon
            if (inventory.getActiveItem()->isWeapon())
            {
                pActiveWeapon = static_cast<Weapon*>(inventory.getActiveItem());
            }
            else
            {
                pActiveWeapon = nullptr;
            }

            // Eating a food
            if (inventory.getActiveItem()->isFood() && 
                attributeComponent->getHp() != attributeComponent->getHpMax() &&
                sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                Food* food = static_cast<Food*>(inventory.getActiveItem());
                int hpToRestore = food->getRestoringHpAmount();

                textTagSystem.addTextTag(
                    HEALING_TAG, 
                    getPosition(), 
                    (hpToRestore + getHp()) > getHpMax() 
                     ? (hpToRestore - (getHp() + hpToRestore - getHpMax()))
                     : hpToRestore
                );
                attributeComponent->gainHp(hpToRestore);

                inventory.removeItem(inventory.getActiveItemIndex());
            } 
        }
        else // if (!inventory.getActiveItem())
        {
            pActiveWeapon = nullptr;
        }


        Character::updateDamageColor();
    }

    else if (!deathAnimationDone) // if (isDead())
    {
        animationComponent->play("IS_DEAD", deltaTime);
        deathAnimationDone = animationComponent->isDone("IS_DEAD");
        sprite.setPosition(getPosition().x - sprite.getTextureRect().width / 2.f, 
                           getPosition().y - sprite.getTextureRect().height / 3.f
                           );
    }
}


void Player::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const sf::Vector2f& shaderLightPosition,
                    const bool showHitbox
                    )
{
    if (!isDead() || !deathAnimationDone)
    {
        Entity::render(target, pShader, shaderLightPosition, showHitbox);
    }
    
    if (!isDead())
    {
        const sf::View view = target.getView();

        inventory.renderToView(target);
        target.setView(target.getDefaultView());
        inventory.renderToWindow(target);

        target.setView(view);
    }
}


bool Player::addItemToInventory(Item* pItem, const bool setAsActive)
{
    assert(pItem != nullptr);
    bool isAdded = inventory.addItem(pItem);

    if (isAdded && setAsActive)
    {
        inventory.setActiveItem(inventory.getSize() - 1);
    }
    return isAdded;
}


void Player::removeActiveItem()
{
    inventory.removeItem(inventory.getActiveItemIndex());

    if (pActiveWeapon)
    {
        pActiveWeapon = nullptr;
    }
}


Item* Player::getActiveItem() const
{
    return inventory.getActiveItem();
}


int Player::getHp() const
{
    return attributeComponent->getHp();
}


int Player::getHpMax() const
{
    return attributeComponent->getHpMax();
}


int Player::getExp() const
{
    return attributeComponent->getExp();
}


int Player::getExpForNextLevel() const
{
    return attributeComponent->getExpForNextLevel();
}


unsigned Player::getLevel() const
{
    return attributeComponent->getLevel();
}


int Player::getDamage() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getDamage() + attributeComponent->getDamage();  
    }
    return Character::getDamage();
}


float Player::getAttackRange() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getRange();
    }
    return 42.f;
}


const std::string Player::getStatsAsString() const
{
    std::stringstream stream;

    stream << "Level: " << attributeComponent->getLevel() << '\n'
           << "Health: " << attributeComponent->getHp() << '\n'
           << "Max Health: " << attributeComponent->getHpMax() << '\n'
           << "Exp: " << attributeComponent->getExp() << '\n'
           << "Exp for the next level: " << attributeComponent->getExpForNextLevel() << "\n\n"
           << "Attack range: " << getAttackRange() << '\n'
           << "Min damage: " << (pActiveWeapon 
                                 ? (pActiveWeapon->getDamageMin() + attributeComponent->getDamageMin())
                                 : attributeComponent->getDamageMin()) << '\n'
           << "Max damage: " << (pActiveWeapon 
                                 ? (pActiveWeapon->getDamageMax() + attributeComponent->getDamageMax())
                                 : attributeComponent->getDamageMax()) << '\n';

    return stream.str();
}


int Player::getNumberOfItems() const
{
    return inventory.getSize();
}


void Player::loseExp(const int exp)
{
    attributeComponent->loseExp(exp);
}


WeaponType Player::getActiveWeaponType() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getWeaponType();
    }
    return MELEE_WEAPON;
}


void Player::gainExp(const int exp)
{
    attributeComponent->gainExp(exp);
}


void Player::setAttackStatus(const bool attacking)
{
    this->attacking = attacking;
}


bool Player::isAttacking() const
{
    return attacking;
}


bool Player::canAttack() const
{
    if (inventory.panelIsActive())
    {
        return false;
    }

    if (pActiveWeapon)
    {
        return pActiveWeapon->canAttack();
    }

    return Character::canAttack();
}


bool Player::deathAnimationIsDone() const
{
    if (!isDead())
    {
        return false;
    }
    return deathAnimationDone;
}


void Player::toggleInventoryPanel()
{
    inventory.togglePanelHiddenStatus();
}


void Player::initTimers()
{
    damageTimerMax = 350;
    attackTimerMax = 200;
}