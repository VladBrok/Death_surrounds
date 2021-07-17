#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "SFML/Graphics.hpp"
#include <unordered_map>


class AnimationComponent: sf::NonCopyable
{
public:

                    AnimationComponent(sf::Texture& textureSheet, sf::Sprite& sprite);
                    ~AnimationComponent();
    
    void            addAnimation(const std::string&    animationKey,
                                 sf::Texture&          textureSheet, 
                                 sf::Sprite&           sprite,
                                 const int             startFrameX,
                                 const int             startFrameY,
                                 const int             endFrameX,
                                 const int             endFrameY,
                                 const int             frameWidth,
                                 const int             frameHeight,
                                 const float           timeToPlayAnimation
                                 );
    void            play(const std::string& animationKey, const float deltaTime);

private:

    class Animation: public sf::NonCopyable
    {
    public:

        sf::Texture&            textureSheet;
        sf::Sprite&             sprite;
        sf::IntRect             startRect;
        sf::IntRect             currentRect;
        sf::IntRect             endRect;
        float                   timeToPlayAnimation;
        float                   animationTimer;


        /*
            In this constructor, variables startFrameX and startFrameY are 
            the numbers of the column and row (starting from 0) in which the starting frame is
            located on the texture sheet. Same for endFrameX and endFrameY.
        */
        Animation(sf::Texture&          textureSheet, 
                  sf::Sprite&           sprite,
                  const int             startFrameX,
                  const int             startFrameY,
                  const int             endFrameX,  
                  const int             endFrameY,  
                  const int             frameWidth, 
                  const int             frameHeight,
                  const float           timeToPlayAnimation  
                  )
                  : textureSheet        (textureSheet),
                    sprite              (sprite),
                    startRect           (startFrameX * frameWidth, startFrameY * frameHeight, frameWidth, frameHeight),
                    currentRect         (startRect),
                    endRect             (endFrameX * frameWidth, endFrameY * frameHeight, frameWidth, frameHeight),
                    timeToPlayAnimation (timeToPlayAnimation),
                    animationTimer      (0.f)
        {         
            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(startRect);
        }

        
        void play(const float deltaTime)
        {
            animationTimer += 100.f * deltaTime;

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
