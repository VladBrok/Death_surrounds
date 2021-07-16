#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "SFML/Graphics.hpp"
#include <unordered_map>


class AnimationComponent
{
public:

                    AnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite);
                    ~AnimationComponent();
    void            addAnimation(const std::string& animationKey);
    void            play(const std::string& animationKey, const float deltaTime);

private:

    class Animation
    {
    public:

        sf::Texture&            textureSheet;
        sf::Sprite&             sprite;
        sf::IntRect             startRect;
        sf::IntRect             currentRect;
        sf::IntRect             endRect;
        float                   timeToPlayAnimation;
        float                   animationTimer;


        Animation(sf::Texture&          textureSheet, 
                  sf::Sprite&           sprite,
                  const int             startFrameNumber,
                  const int             endFrameNumber,
                  const int             width,
                  const int             height,
                  const float           timeToPlayAnimation
                  )
                  : textureSheet        (textureSheet),
                    sprite              (sprite),
                    startRect           (startFrameNumber * width, startFrameNumber * height, width, height),
                    currentRect         (startRect),
                    endRect             (endFrameNumber * width, endFrameNumber * height, width, height),
                    timeToPlayAnimation (timeToPlayAnimation),
                    animationTimer      (0.f)
        {
            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(startRect);
        }

        
        void play(const float deltaTime)
        {
            animationTimer += 10.f * deltaTime;

            if (animationTimer >= timeToPlayAnimation)
            {
                animationTimer = 0.f;
                if (currentRect != endRect) // Animate
                {
                    currentRect.left += currentRect.width;
                }
                else // Reset texture
                {
                    currentRect.left = startRect.left;
                }

                sprite.setTextureRect(currentRect);
            }
        }


        void reset()
        {
            animationTimer = 0.f;
            currentRect = startRect;
        }

    };

    sf::Texture&                                  textureSheet;
    sf::Sprite&                                   sprite;
    std::unordered_map<std::string, Animation*>   animations;

};


#endif // ANIMATION_COMPONENT_H