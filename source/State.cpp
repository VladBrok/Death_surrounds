#include "precompiled.h"
#include "State.h"
#include "constants.h"
#include "Resources.h"


State::State(sf::RenderWindow& window, 
             const StringToKeyMap& supportedKeys,
             std::stack<std::unique_ptr<State>>& states
            )
    : window(window), 
      supportedKeys(supportedKeys), 
      states(states), 
      stateIsActive(true),
      stateIsPaused(false)
{
    initFont();
}


void State::processEvent(const sf::Event&)
{
    // Do nothing by default
}


void State::update(const float)
{
    // Do nothing by default
}


bool State::isActive() const 
{
    return stateIsActive;
}


void State::endActivity()
{
    stateIsActive = false;
}


void State::pauseState()
{
    stateIsPaused = true;
}


void State::unpauseState()
{
    stateIsPaused = false;
}


void State::initFont()
{
    if (!font.loadFromFile(resources::getFontFile()))
    {
        throw std::runtime_error("ERROR in State::initFont: could not load the font from file " + resources::getFontFile());
    }
}


void State::updateMousePosition(sf::View* pView)
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(window);

    if (pView)
    {
        window.setView(*pView);
    }

    mousePosView = window.mapPixelToCoords(mousePosWindow);
    window.setView(window.getDefaultView());

    mousePosGrid.x = static_cast<int>(mousePosView.x) / static_cast<int>(GRID_SIZE);
    mousePosGrid.y = static_cast<int>(mousePosView.y) / static_cast<int>(GRID_SIZE);
}


void State::initTextures()
{
    // Do nothing by default
}


void State::initKeybinds(const std::string& filePath)
{
    std::ifstream file(filePath);

    // Loading the keys for the state
    if (file.is_open()) 
    {
        std::string action;
        std::string key;
        try
        {
            while (file >> action >> key)
            {
                keybinds[action] = supportedKeys.at(key);
            }
        }
        catch (std::out_of_range&)
        {
            throw std::runtime_error(
                      "ERROR in State::initKeybinds: "
                      "the required keys could not be found among the supported ones\n"
                       );
        }
    }
    else
    {
        throw std::runtime_error("ERROR in State::initKeybinds: unable to open the file " + filePath + "\n");
    }
}
