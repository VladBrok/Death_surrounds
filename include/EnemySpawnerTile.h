#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"
class EnemySystem;


class EnemySpawnerTile: public Tile
{
public:

                                EnemySpawnerTile(const float posX, 
                                                 const float posY, 
                                                 const sf::Texture& textureSheet,
                                                 const sf::IntRect& textureRect,
                                                 const bool canCollide,
                                                 const int enemyType,
                                                 const int enemyTimeToSpawn
                                                 );
    void                        update(EnemySystem& enemySystem);        

   /* 
      Returns the string with textureRect position, collision ability,
      enemyType and enemyTimeToSpawn varibales
   */
   virtual const std::string    getAsString() const; 

private:
    
    int                         enemyType;
    int                         enemyTimeToSpawn;
    sf::Clock                   spawnTimer;
};


#endif // ENEMYSPAWNERTILE_H
