#include "precompiled.h"
#include "EnemySystem.h"
#include "Rat.h"


EnemySystem::EnemySystem(std::list<Enemy*>& activeEnemies, 
            std::unordered_map<std::string, sf::Texture>& textures
            )
            : activeEnemies(activeEnemies), textures(textures)
{
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


int EnemySystem::getNumberOfActiveEnemies() const
{
    return (int)activeEnemies.size();
}