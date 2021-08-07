#include "precompiled.h"
#include "Utils.h"


namespace utils
{


float percentToPixels(const float percent, const int size)
{
    return size * (percent / 100.f);
}

    
float getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return std::sqrt( std::powf(point2.x - point1.x, 2.f) + std::powf(point2.y - point1.y, 2.f) );
}


const sf::Vector2f getNormalizedDirection(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    sf::Vector2f direction(point2 - point1);

    const float directionLength = std::sqrtf( direction.x * direction.x + direction.y * direction.y );

    direction /= directionLength; // Normalizing the direction vector

    return direction;
}


void lookAt(sf::Sprite& object, const sf::Vector2f& pointToLookAt, const float offset)
{
    sf::Vector2f direction(utils::getNormalizedDirection(object.getPosition(), pointToLookAt));

    const float PI = 3.14159265358979323846f;
    const float degree = std::atan2f(direction.y, direction.x) * 180 / PI;
    object.setRotation(static_cast<int>(degree + offset));
}


} // namespace utils
