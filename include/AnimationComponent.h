#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H


class AnimationComponent: sf::NonCopyable
{
public:

                            AnimationComponent(const sf::Texture& textureSheet, sf::Sprite& sprite);
                            ~AnimationComponent();
    /*
        Variables startFrameX and startFrameY are 
        numbers of the column and the row (starting from 0) in which the starting frame is
        located on the texture sheet
    */  
    void                    addAnimation(const std::string&    animationKey,
                                         const sf::Texture&    textureSheet, 
                                         sf::Sprite&           sprite,
                                         const int             startFrameX,
                                         const int             startFrameY,
                                         const int             endFrameX,
                                         const int             endFrameY,
                                         const int             frameWidth,
                                         const int             frameHeight,
                                         const float           timeToPlayAnimation
                                         );
                     
    void                    play(const std::string& animationKey,
                                 const float deltaTime, 
                                 const float animationSpeedModifier = 1.f, 
                                 const float animationSpeedModifierMax = 1.f,
                                 const bool priority = false
                                 );

    // Returns true if animation is finished
    bool                    isDone(const std::string& animationKey) const; 

private:


    class Animation: public sf::NonCopyable
    {
    public:

        const sf::Texture&      textureSheet;
        sf::Sprite&             sprite;
        sf::IntRect             startRect;
        sf::IntRect             currentRect;
        sf::IntRect             endRect;
        float                   timeToPlayAnimation;
        float                   animationTimer;
        bool                    done; // Done is true if animation is finished


        Animation(const sf::Texture&    textureSheet, 
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

  
        void play(const float deltaTime, float speedModifier)
        {
            if (speedModifier < 0.9f)
            {
                speedModifier = 0.9f;
            }
            animationTimer += speedModifier * 100.f * deltaTime;


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

    typedef std::unordered_map<std::string, Animation*>  StringToAnimationMap;


    const sf::Texture&      textureSheet;
    sf::Sprite&             sprite;
    StringToAnimationMap    animations;
    Animation*              pLastAnimation;
    Animation*              pPriorityAnimation; // This animation will be playing until it's done
                            
    void                    updateLastAnimation(const std::string& animationKey);

};


#endif // ANIMATION_COMPONENT_H
