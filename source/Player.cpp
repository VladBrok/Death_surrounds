#include "precompiled.h"
#include "Player.h"
#include "Food.h"


Player::Player(const float posX, 
               const float posY, 
               const sf::Texture& textureSheet,
               const sf::Texture& inventoryPanelTexture,
               const sf::RenderWindow& window
               )
    : Character(textureSheet), inventory(window, inventoryPanelTexture), pActiveWeapon(nullptr)
{

    createMovementComponent(200.f, 1600.f, 1000.f);
    createAnimationComponent(textureSheet);
    createHitboxComponent(18.f, 25.f, 28.f, 30.f);
    createAttributeComponent(1, 10, 1, 2);

    pAnimationComponent->addAnimation("IDLE", textureSheet, sprite, 0, 0, 8, 0, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_LEFT", textureSheet, sprite, 4, 1, 7, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_RIGHT", textureSheet, sprite, 8, 1, 11, 1, 64, 64, 9.5f);
    pAnimationComponent->addAnimation("MOVING_UP", textureSheet, sprite, 12, 1, 15, 1, 64, 64, 9.5f );

    setPosition(posX, posY);

    initTimers();
}


void Player::update(const float deltaTime, 
                    const sf::Vector2f& mousePosView, 
                    const sf::Vector2i& mousePosWindow,
                    TextTagSystem& textTagSystem
                    )
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

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

        // Eating the food
        if (inventory.getActiveItem()->isFood() && 
            pAttributeComponent->hp != pAttributeComponent->hpMax &&
            sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            Food* food = static_cast<Food*>(inventory.getActiveItem());
            int hpToRestore = (int)food->getRestoringHpAmount();

            textTagSystem.addTextTag(
                HEALING_TAG, 
                getPosition(), 
                (hpToRestore + getHp()) > getHpMax() ? (hpToRestore - (getHp() + hpToRestore - getHpMax())): hpToRestore
            );
            pAttributeComponent->gainHp(hpToRestore);

            inventory.removeItem(inventory.getActiveItemIndex());
        } 
    }
    else
    {
        pActiveWeapon = nullptr;
    }


    Character::updateDamageColor();
}


void Player::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const sf::Vector2f& shaderLightPosition,
                    const bool showHitbox
                    )
{
    Entity::render(target, pShader, shaderLightPosition, showHitbox);
    

    const sf::View view = target.getView();

    inventory.renderToView(target);
    target.setView(target.getDefaultView());
    inventory.renderToWindow(target);

    target.setView(view);
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
    return pAttributeComponent->hp;
}


int Player::getHpMax() const
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


void Player::loseExp(const unsigned exp)
{
    pAttributeComponent->loseExp(exp);
}


WeaponType Player::getActiveWeaponType() const
{
    if (pActiveWeapon)
    {
        return pActiveWeapon->getWeaponType();
    }
    return MELEE_WEAPON;
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


void Player::toggleInventoryPanel()
{
    inventory.togglePanelHiddenStatus();
}


void Player::initTimers()
{
    damageTimerMax = 350;
    attackTimerMax = 200;
}