#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite)
    : textureSheet(textureSheet), sprite(sprite), pLastAnimation(nullptr)
{
}


AnimationComponent::~AnimationComponent()
{
    for (auto a = animations.begin(); a != animations.end(); ++a)
    {
        delete a->second;
    }
}


void AnimationComponent::addAnimation(
    const std::string&    animationKey,
    sf::Texture&          textureSheet, 
    sf::Sprite&           sprite,
    const int             startFrameX,
    const int             startFrameY,
    const int             endFrameX,
    const int             endFrameY,
    const int             frameWidth,
    const int             frameHeight,
    const float           timeToPlayAnimation
    )
{
    animations[animationKey] = new Animation(
                                    textureSheet, 
                                    sprite, 
                                    startFrameX, 
                                    startFrameY,
                                    endFrameX,
                                    endFrameY,
                                    frameWidth,
                                    frameHeight,
                                    timeToPlayAnimation
                               );
}


void AnimationComponent::play(const std::string& animationKey, const float deltaTime)
{
    if (animations.at(animationKey) != pLastAnimation)
    {
        if (!pLastAnimation) // No animations were played in this component before
        {
            pLastAnimation = animations[animationKey];
        }
        else
        {
            pLastAnimation->reset(); // Reseting the last played animation
            pLastAnimation = animations[animationKey];
        }
    }
    animations[animationKey]->play(deltaTime);
}