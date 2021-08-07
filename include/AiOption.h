#ifndef AIOPTION_H
#define AIOPTION_H

#include "Entity.h"


class AiOption: public sf::NonCopyable
{
public:

                    AiOption(Entity& self, Entity& targetEntity);
    virtual void    update(const float deltaTime) = 0;

protected:

    Entity&         self;
    Entity&         targetEntity;
};


#endif // AIOPTION_H
