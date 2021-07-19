#include "SettingsState.h"


SettingsState::SettingsState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates)
{
    initTextures();
    initFont();
    initButtons();
    initBackground();
}


SettingsState::~SettingsState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    
}


void SettingsState::update(const float deltaTime)
{
    updateMousePosition();

    updateButtons();
}


void SettingsState::updateKeyboardInput(const float deltaTime)
{
}


void SettingsState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }
    pTarget->draw(background);

    renderButtons();
}


void SettingsState::updateButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->update(mousePosView);
    }

    if (buttons["EXIT_STATE"]->isPressed()) // Exit the state
    {
        endActivity();
    }
}


void SettingsState::renderButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(window);
    }
}


void SettingsState::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void SettingsState::initButtons()
{
    const sf::Vector2f buttonSize(
        static_cast<float>(window.getSize().x / 7),
        static_cast<float>(window.getSize().y / 11)
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["EXIT_STATE"] = new Button(window.getSize().x / 6.f, window.getSize().y / 1.15f, 
                                       buttonSize.x, buttonSize.y, 
                                       font, 
                                       "Quit",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );
}


void SettingsState::initBackground()
{
    background.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    background.setTexture(&textures.at("BACKGROUND"));
}


void SettingsState::initTextures()
{
    textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}