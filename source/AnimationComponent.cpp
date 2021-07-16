#include "AnimationComponent.h"


AnimationComponent::AnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite)
    : textureSheet(textureSheet), sprite(sprite)
{
}


AnimationComponent::~AnimationComponent()
{
    for (auto a = animations.begin(); a != animations.end(); ++a)
    {
        delete a->second;
    }
}


void AnimationComponent::addAnimation(const std::string& animationKey)
{
    //animations[animationKey] = new Animation(
}