#ifndef TYPEDEFS_H
#define TYPEDEFS_H

class Button;
class DropDownList;


typedef std::unordered_map<std::string, sf::Keyboard::Key> StringToKeyMap;

typedef std::unordered_map<std::string, sf::Texture> StringToTextureMap;

typedef std::unordered_map<std::string, Button*> StringToButtonMap;

typedef std::unordered_map<std::string, DropDownList*> StringToDropDownListMap;


#endif // TYPEDEFS_H
