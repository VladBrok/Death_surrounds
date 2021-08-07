#ifndef AIFOLLOW_H
#define AIFOLLOW_H


#include "AiOption.h"


class AiFollow: public AiOption
{
public:

                    AiFollow(Entity& self, Entity& targetEntity);
    virtual void    update(const float deltaTime);
};


#endif // AIFOLLOW_H
