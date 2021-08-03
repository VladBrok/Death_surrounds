#include "precompiled.h"
#include "EnemySystem.h"
#include "Rat.h"


EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, 
            std::unordered_map<std::string, sf::Texture>& textures
            )
            : activeEnemies(activeEnemies), textures(textures)
{
}


void EnemySystem::update(const float deltaTime, const sf::Vector2f& mousePosView)
{
    for (size_t i = 0; i < activeEnemies.size(); ++i)
    {
        activeEnemies[i]->update(deltaTime, mousePosView);
    }
}


void EnemySystem::render(sf::RenderTarget& target,
                         sf::Shader& shader,
                         const sf::Vector2f& shaderLightPosition,
                         const bool showHitbox
                         )
{
    for (size_t i = 0; i < activeEnemies.size(); ++i)
    {
        activeEnemies[i]->render(target, &shader, shaderLightPosition, true);
    }
}


void EnemySystem::createEnemy(const float posX,
                              const float posY,
                              const int type
                              )
{
    switch (type)
    {
    case RAT:
        {
            activeEnemies.push_back(new Rat(posX, posY, textures["ENEMY_RAT_SHEET"]));
        }
        break;
    default:
        throw std::runtime_error("ERROR in EnemySystem::createEnemy: invalid enemy type");
    }
}


const std::string EnemySystem::getEnemyTypeAsString(const int type)
{
    switch (type)
    {
    case RAT:
        return "RAT";
    default:
        return "ERROR_ENEMY_TYPE";
    }
}