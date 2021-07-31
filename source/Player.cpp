#include "precompiled.h"
#include "Player.h"


Player::Player(const float posX, const float posY, sf::Texture& textureSheet)
    : Entity(textureSheet), isAttacking(false)
{
    createMovementComponent(200.f, 1600.f, 1000.f);

    createAnimationComponent(textureSheet);

    createHitboxComponent(17.f, 9.f, 30.f, 50.f);

    createAttributeComponent(1);

    pAnimationComponent->addAnimation(
        "PLAYER_IDLE", textureSheet, sprite, 0, 0, 8, 0, 64, 64, 9.5f
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_DOWN", textureSheet, sprite, 0, 1, 3, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_LEFT", textureSheet, sprite, 4, 1, 7, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_RIGHT", textureSheet, sprite, 8, 1, 11, 1, 64, 64, 9.5f 
    );

    pAnimationComponent->addAnimation(
        "PLAYER_MOVING_UP", textureSheet, sprite, 12, 1, 15, 1, 64, 64, 9.5f 
    );

    setPosition(posX, posY);


    // Weapon test
    weaponTexture.loadFromFile("Resources\\Images\\Entities\\Player\\sword.png");
    weapon.setTexture(weaponTexture);
    weapon.setOrigin(
        weapon.getGlobalBounds().width / 2.f,
        weapon.getGlobalBounds().height
    );
    weapon.setPosition(getCenter());
}


Player::~Player()
{
}


void Player::update(const float deltaTime, const sf::Vector2f& mousePosView)
{
    pMovementComponent->updateMovement(deltaTime);

    updateAnimation(deltaTime);

    pHitboxComponent->update();

    // Weapon test
    weapon.setPosition(getCenter());

    // Making the weapon point towards the mouse
    sf::Vector2f direction(mousePosView - weapon.getPosition());

    const float dirLength = std::sqrtf(direction.x * direction.x + direction.y * direction.y);

    direction /= dirLength; // Normalizing the direction vector

    const float PI = 3.14159265358979323846f;
    const float degree = std::atan2f(direction.y, direction.x) * 180 / PI;
    weapon.setRotation(degree + 90.f);
}


void Player::render(sf::RenderTarget& target, 
                    sf::Shader* pShader,
                    const bool showHitbox
                    )
{
    Entity::render(target, pShader, showHitbox);

    // Weapon test
    target.draw(weapon);
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


void Player::loseHP(const unsigned points)
{
    pAttributeComponent->loseHP(points);
}


void Player::gainHP(const unsigned points)
{
    pAttributeComponent->gainHP(points);
}


void Player::loseExp(const unsigned exp)
{
    pAttributeComponent->loseExp(exp);
}


void Player::gainExp(const unsigned exp)
{
    pAttributeComponent->gainExp(exp);
}


void Player::updateAttack()
{
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
            "PLAYER_" + movementState, 
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
