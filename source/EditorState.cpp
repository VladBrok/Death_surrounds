#include "precompiled.h"
#include "EditorState.h"
#include "constants.h"


EditorState::EditorState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates), tileMap(5, 5, 1)
{
    stateIsEventHandler = true;

    initKeybinds("Config//editorstate_keybinds.ini");
    initTextures();
    initButtons();
    initPauseMenu();
    initTileSelector();
}


EditorState::~EditorState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    

    delete pPauseMenu;
}


void EditorState::processEvents(const sf::Event& event)
{
    if (stateIsPaused)
    {
        processPauseMenuButtonEvents(event);
    }
    else
    {
        updateTileSelector();

        for (auto b = buttons.begin(); b != buttons.end(); ++b)
        {
            b->second->processMouseEvent(event, mousePosView);
        }
    }

    if (event.type == sf::Event::KeyPressed &&
        event.key.code == keybinds.at("CLOSE_STATE"))
    {
        stateIsPaused ? unpauseState(): pauseState();
    }
}


void EditorState::processPauseMenuButtonEvents(const sf::Event& event)
{
    pPauseMenu->processMouseEvent(event, mousePosView);

    if (pPauseMenu->isButtonPressed("QUIT"))
    {
        endActivity();
    }
}


void EditorState::update(const float deltaTime)
{
    updateMousePosition();
}


void EditorState::updateTileSelector()
{
    tileSelector.setPosition(mousePosGrid.x * GRID_SIZE, mousePosGrid.y * GRID_SIZE);
}


void EditorState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }

    tileMap.render(*pTarget);
    pTarget->draw(tileSelector);

    if (stateIsPaused)
    {
        pPauseMenu->render(*pTarget);
    }
    else
    {
        renderButtons(*pTarget);
    }
}


void EditorState::renderButtons(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }
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


void EditorState::initPauseMenu()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
    pPauseMenu = new PauseMenu(window, font);

    pPauseMenu->addButton("QUIT", "Go to main menu", 5);
}


void EditorState::initTileSelector()
{
    tileSelector.setSize(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    tileSelector.setFillColor(sf::Color::Transparent);
    tileSelector.setOutlineThickness(1.f);
    tileSelector.setOutlineColor(sf::Color::Magenta);
}