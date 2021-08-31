#include "precompiled.h"
#include "EnemySystem.h"
#include "Rat.h"
#include "Spider.h"
#include "Skeleton.h"
#include "constants.h"
#include "Reaper.h"


EnemySystem::EnemySystem(std::list<std::unique_ptr<Enemy>>& activeEnemies, 
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

    // TODO: Refactor
    switch (type)
    {
    case RAT:
        {
            std::unique_ptr<Enemy> rat(new Rat(posX, posY, textures.at("ENEMY_RAT_SHEET"), textures.at("FOOD"), player));
            activeEnemies.push_back(std::move(rat));
            break;
        }
    case SPIDER:
        {
            std::unique_ptr<Enemy> spider(new Spider(posX, posY, textures.at("ENEMY_SPIDER_SHEET"), textures.at("FOOD"), player));
            activeEnemies.push_back(std::move(spider));
            break;
        }
    case SKELETON:
        {
            std::unique_ptr<Enemy> skeleton(new Skeleton(posX, posY, textures.at("ENEMY_SKELETON_SHEET"), textures.at("FOOD"), player));
            activeEnemies.push_back(std::move(skeleton));
            break;
        }
    case REAPER:
        {
            std::unique_ptr<Enemy> reaper(new Reaper(posX, posY, textures.at("ENEMY_REAPER_SHEET"), textures.at("FOOD"), player, *this));
            activeEnemies.push_back(std::move(reaper));
            break;
        }
    default:
        std::cout << "ERROR in EnemySystem::createEnemy: invalid enemy type\n";
        assert(false);
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
