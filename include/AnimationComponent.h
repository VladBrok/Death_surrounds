#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>


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
    void            play(const std::string& animationKey, const float deltaTime, const bool priority = false);

    /* 
        This play function allows you to modify an animation speed 
        depending on certain circumstances
    */
    void            play(const std::string& animationKey,
                         const float deltaTime, 
                         const float modifier, 
                         const float modifierMax,
                         const bool priority = false
                         );
    bool            isDone(const std::string& animationKey) const; // Returns true if animation is finished

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
        bool                    done; // Done is true if animation is finished


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
                    animationTimer      (0.f),
                    done                (false)
        {         
            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(startRect);
        }

        
        void play(const float deltaTime)
        {
            animationTimer += 100.f * deltaTime;

            animateIfTimerAllows();
        }

        
        void play(const float deltaTime, float modifier)
        {
            if (modifier < 0.5f)
            {
                modifier = 0.5f;
            }
            animationTimer += modifier * 100.f * deltaTime;

            animateIfTimerAllows();
        }


        void animateIfTimerAllows()
        {
            if (animationTimer >= timeToPlayAnimation)
            {
                animationTimer = 0.f;
                if (currentRect != endRect) // Animate
                {
                    currentRect.left += currentRect.width;
                    done = false;
                }
                else // Reset texture
                {
                    currentRect.left = startRect.left;
                    done = true;
                }
                sprite.setTextureRect(currentRect);
            }
        }


        void reset()
        {
            animationTimer = timeToPlayAnimation;
            currentRect.left = startRect.left;
        }

        
        bool isDone() const
        {
            return done;
        }

    };

    sf::Texture&                                  textureSheet;
    sf::Sprite&                                   sprite;
    std::unordered_map<std::string, Animation*>   animations;
    Animation*                                    pLastAnimation;
    Animation*                                    pPriorityAnimation; // This animation will be playing until it's done

    void                                          updateLastAnimation(const std::string& animationKey);

};


#endif // ANIMATION_COMPONENT_H
