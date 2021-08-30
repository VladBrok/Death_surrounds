#include "precompiled.h"
#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(const sf::Texture& textureSheet, sf::Sprite& sprite)
    : textureSheet(textureSheet), 
      sprite(sprite), 
      pLastAnimation(nullptr), 
      pPriorityAnimation(nullptr)
{
}


void AnimationComponent::addAnimation(const std::string& animationKey,
                                      const sf::Texture& textureSheet, 
                                      sf::Sprite&        sprite,
                                      const int          startFrameX,
                                      const int          startFrameY,
                                      const int          endFrameX,
                                      const int          endFrameY,
                                      const int          frameWidth,
                                      const int          frameHeight,
                                      const float        timeToPlayAnimation
                                      )
{
    animations[animationKey].reset(
        new Animation(
              textureSheet, 
              sprite, 
              startFrameX, 
              startFrameY,
              endFrameX,
              endFrameY,
              frameWidth,
              frameHeight,
              timeToPlayAnimation
        )
    );
}


 void AnimationComponent::play(const std::string& animationKey, 
                               const float deltaTime, 
                               const float animationSpeedModifier, 
                               const float animationSpeedModifierMax,
                               const bool  priority
                               )
{
    updateLastAnimation(animationKey);

    if (!pPriorityAnimation)
    {
        animations[animationKey]->play(deltaTime, std::abs(animationSpeedModifier / animationSpeedModifierMax));
        if (priority)
        {
            pPriorityAnimation = animations[animationKey].get();
        }
    }
    else
    {
        pPriorityAnimation->play(deltaTime, std::abs(animationSpeedModifier / animationSpeedModifierMax));
        if (pPriorityAnimation->isDone())
        {
            pPriorityAnimation = nullptr;
        }
    }
}


bool AnimationComponent::isDone(const std::string& animationKey) const
{
    return animations.at(animationKey)->isDone();
}


 void AnimationComponent::updateLastAnimation(const std::string& animationKey)
 {
    if (animations.at(animationKey).get() != pLastAnimation)
    {
        // No animations were played before
        if (!pLastAnimation) 
        {
            pLastAnimation = animations[animationKey].get();
        }
        else
        {
            // Reseting the last played animation
            pLastAnimation->reset(); 
            pLastAnimation = animations[animationKey].get();
        }
    }
 }