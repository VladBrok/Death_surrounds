#include "EditorState.h"


EditorState::EditorState(sf::RenderWindow* pWindow,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(pWindow, pSupportedKeys, pStates)
{
    initKeybinds("Config//editorstate_keybinds.ini");
    initTextures();
    initFont();
    initButtons();
}


EditorState::~EditorState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    
}


void EditorState::update(const float deltaTime)
{
    updateMousePosition();

    updateButtons();

    updateKeyboardInput(deltaTime);
}


void EditorState::updateKeyboardInput(const float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("CLOSE_STATE")))
    {
        endActivity();
    }
}


void EditorState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = pWindow;
    }

    renderButtons();
}


void EditorState::updateButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->update(mousePosView);
    }
}


void EditorState::renderButtons()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(*pWindow);
    }
}


void EditorState::initFont()
{
    font.loadFromFile("Fonts\\PixellettersFull.ttf");
}


void EditorState::initButtons()
{
    //const sf::Vector2f buttonSize(
    //    static_cast<float>(pWindow->getSize().x / 6),
    //    static_cast<float>(pWindow->getSize().y / 10)
    //);
    //const sf::Color textIdleColor(sf::Color(150, 150, 150));
    //const sf::Color textHoverColor(sf::Color::White);
    //const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    //buttons["GAME_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 2.2f, 
    //                                   buttonSize.x, buttonSize.y,
    //                                   &font, 
    //                                   "New game",
    //                                   textIdleColor,
    //                                   textHoverColor,
    //                                   textActiveColor
    //                                   );

    //buttons["SETTINGS_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.75f, 
    //                                       buttonSize.x, buttonSize.y,
    //                                       &font, 
    //                                       "Settings",
    //                                       textIdleColor,
    //                                       textHoverColor,
    //                                       textActiveColor
    //                                       );

    //buttons["EXIT_STATE"] = new Button(pWindow->getSize().x / 6.f, pWindow->getSize().y / 1.3f, 
    //                                   buttonSize.x, buttonSize.y, 
    //                                   &font, 
    //                                   "Quit",
    //                                   textIdleColor,
    //                                   textHoverColor,
    //                                   textActiveColor
    //                                   );
}


void EditorState::initTextures()
{
    //textures["BACKGROUND"].loadFromFile("Images\\Backgrounds\\main_menu_bg.png");
}