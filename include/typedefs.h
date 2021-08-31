#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "Button.h"
#include "DropDownList.h"


typedef std::unordered_map<std::string, sf::Keyboard::Key>             StringToKeyMap;
                                                                     
typedef std::unordered_map<std::string, sf::Texture>                   StringToTextureMap;

typedef std::unordered_map<std::string, std::unique_ptr<Button>>       StringToButtonMap;

typedef std::unordered_map<std::string, std::unique_ptr<DropDownList>> StringToDropDownListMap;


#endif // TYPEDEFS_H
