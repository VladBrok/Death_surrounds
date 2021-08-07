#ifndef UTILS_H
#define UTILS_H


namespace utils
{


// Coverts the percent value of the size to pixels 
float percentToPixels(const float percent, const int size);

// Returns the distance between two points
float getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);

// Calculates the vector between two points and normalizes it
const sf::Vector2f getNormalizedDirection(const sf::Vector2f& point1, const sf::Vector2f& point2);

// Rotates the object so that it points towards the specific point
void lookAt(sf::Sprite& object, const sf::Vector2f& pointToLookAt, const float offset = 90.f);


} // namespace utils


#endif // UTILS_H
