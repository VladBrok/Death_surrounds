#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H


class Enemy;
class Entity;


enum EnemyType
{
    RAT,
    NUMBER_OF_ENEMY_TYPES
};


class EnemySystem: public sf::NonCopyable
{
public:

                                                   EnemySystem(std::list<Enemy*>& activeEnemies, 
                                                               std::unordered_map<std::string, sf::Texture>& textures,
                                                               Entity& player
                                                               );
     void                                          createEnemy(const float posX,
                                                               const float posY,
                                                               const int type
                                                               );
     static const std::string                      getEnemyTypeAsString(const int type);
     int                                           getNumberOfActiveEnemies() const;

private:

    std::list<Enemy*>&                             activeEnemies;
    std::unordered_map<std::string, sf::Texture>&  textures;
    Entity&                                        player;
};


#endif // ENEMYSYSTEM_H
