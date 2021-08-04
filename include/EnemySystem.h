#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H


class Enemy;


enum EnemyType
{
    RAT,
    NUMBER_OF_ENEMY_TYPES
};



class EnemySystem: public sf::NonCopyable
{
public:

                                                   EnemySystem(std::vector<Enemy*>& activeEnemies, 
                                                               std::unordered_map<std::string, sf::Texture>& textures
                                                               );
     void                                          createEnemy(const float posX,
                                                               const float posY,
                                                               const int type
                                                               );
     static const std::string                      getEnemyTypeAsString(const int type);

private:

    std::vector<Enemy*>&                           activeEnemies;
    std::unordered_map<std::string, sf::Texture>&  textures;
};


#endif // ENEMYSYSTEM_H
