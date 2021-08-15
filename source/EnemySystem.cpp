#include "precompiled.h"
#include "EnemySystem.h"
#include "Rat.h"
#include "Spider.h"
#include "Skeleton.h"
#include "constants.h"
#include "Reaper.h"


EnemySystem::EnemySystem(std::list<Enemy*>& activeEnemies, 
                         StringToTextureMap& textures,
                         Entity& player
                         )
 : activeEnemies(activeEnemies), 
   textures(textures),
   player(player)
{
}


void EnemySystem::createEnemy(const float posX,
                              const float posY,
                              const int type
                              )
{
    if (getNumberOfActiveEnemies() >= NUMBER_OF_ACTIVE_ENEMIES_MAX)
    {
        return;
    }


    switch (type)
    {
    case RAT:
        {
            activeEnemies.push_back(new Rat(posX, posY, textures.at("ENEMY_RAT_SHEET"), textures.at("FOOD"), player));
            break;
        }
    case SPIDER:
        {
            activeEnemies.push_back(new Spider(posX, posY, textures.at("ENEMY_SPIDER_SHEET"), textures.at("FOOD"), player));
            break;
        }
    case SKELETON:
        {
            activeEnemies.push_back(new Skeleton(posX, posY, textures.at("ENEMY_SKELETON_SHEET"), textures.at("FOOD"), player));
            break;
        }
    case REAPER:
        {
            activeEnemies.push_back(new Reaper(posX, posY, textures.at("ENEMY_REAPER_SHEET"), textures.at("FOOD"), player, *this));
            break;
        }
    default:
        std::cout << "ERROR in EnemySystem::createEnemy: invalid enemy type\n";
    }
}


const std::string EnemySystem::getEnemyTypeAsString(const int type)
{
    switch (type)
    {
    case RAT:
        return "RAT";
    case SPIDER:
        return "SPIDER";
    case SKELETON:
        return "SKELETON";
    case REAPER:
        return "REAPER";
    default:
        return "ERROR_ENEMY_TYPE";
    }
}


int EnemySystem::getNumberOfActiveEnemies() const
{
    return (int)activeEnemies.size();
}
