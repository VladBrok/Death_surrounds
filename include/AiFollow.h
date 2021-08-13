#ifndef AIFOLLOW_H
#define AIFOLLOW_H

#include "Entity.h"


class AiFollow: public sf::NonCopyable
{
public:

               AiFollow(Entity& self, Entity& targetEntity);
    void       update(const float deltaTime);
    Entity&    getTargetEntity() const;

private:

    Entity&    self;
    Entity&    targetEntity;
};


#endif // AIFOLLOW_H
