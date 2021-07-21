#include "precompiled.h"
#include "SettingsState.h"


SettingsState::SettingsState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>* const pSupportedKeys,
                             std::stack<State*>* const pStates
                             )
    : State(window, pSupportedKeys, pStates)
{
    stateIsEventHandler = true;

    initTextures();
    initFont();
    initGui();
    initBackground();
}


SettingsState::~SettingsState()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    

    for (auto d = dropDownLists.begin(); d != dropDownLists.end(); ++d)
    {
        delete d->second;
    } 
}


void SettingsState::processEvents(const sf::Event& event)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processMouseEvent(event, mousePosView);
    }

    for (auto d = dropDownLists.begin(); d != dropDownLists.end(); ++d)
    {
        d->second->processMouseEvent(event, mousePosView);
    }

    // Reacting on the pressed buttons
    if (buttons["APPLY"]->isPressed()) // FIXME: actually you need to restart game for proper window resize
    {
        sf::Vector2u resolution(
            getResolutionFromString(
                dropDownLists["RESOLUTION"]->getActiveElementText()
            )
        );
        window.setSize(resolution);
    }
    else if (buttons["EXIT_STATE"]->isPressed())
    {
        endActivity();
    }
}


void SettingsState::update(const float deltaTime)
{
    updateMousePosition();
}


void SettingsState::render(sf::RenderTarget* pTarget)
{
    if (!pTarget)
    {
        pTarget = &window;
    }
    pTarget->draw(background);
    
    renderGui(*pTarget);
}


void SettingsState::renderGui(sf::RenderTarget& target)
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->render(target);
    }

    for (auto d = dropDownLists.begin(); d != dropDownLists.end(); ++d)
    {
        d->second->render(target);
    }
}


void SettingsState::initFont()
{
    font.loadFromFile("Fonts\\Dosis-Light.ttf");
}


void SettingsState::initGui()
{
    /*=============== Buttons ===============*/

    const sf::Vector2f buttonSize(
        static_cast<float>(window.getSize().x / 7),
        static_cast<float>(window.getSize().y / 11)
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["APPLY"] = new Button(window.getSize().x / 2.f, window.getSize().y / 1.15f, 
                                       buttonSize.x, buttonSize.y, 
                                       font, 
                                       "Apply",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    buttons["EXIT_STATE"] = new Button(window.getSize().x / 1.2f, window.getSize().y / 1.15f, 
                                       buttonSize.x, buttonSize.y, 
                                       font, 
                                       "Back",
                                       textIdleColor,
                                       textHoverColor,
                                       textActiveColor
                                       );

    /*=============== Drop down lists ===============*/
    
    const std::vector<sf::VideoMode>& videoModes = sf::VideoMode::getFullscreenModes();
    std::vector<std::string> resolutions;
    resolutions.reserve(videoModes.size());

    int activeResolutionIndex = 0;

    for (int i = 0; i < 7; ++i)
    {
        resolutions.push_back(
            std::to_string((long long)videoModes[i].width) + "x" + 
            std::to_string((long long)videoModes[i].height)
        );
        if (videoModes[i].width == window.getSize().x &&
            videoModes[i].height == window.getSize().y)
        {
            activeResolutionIndex = i;
        }
    }

    dropDownLists["RESOLUTION"] = 
        new DropDownList(
             300.f, 300.f, 200.f, 50.f, font, resolutions, activeResolutionIndex
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


sf::Vector2i SettingsState::getResolutionFromString(const std::string& string)
{
    try
    {
        std::string data(string);
        int x_pos = data.find('x');

        if (x_pos == -1)
        {
            throw std::logic_error("");
        }

        int width = 0;
        int height = 0;
        data[x_pos] = ' ';
        std::stringstream str(data);
        str >> width >> height;

        if (str.fail())
        {
            throw std::logic_error("");
        }

        return sf::Vector2i(width, height);
    }
    catch (std::logic_error&)
    {
        throw std::logic_error("ERROR in SettingsState::getResolutionFromString: invalid argument.\n"
                               "Proper string example: 800 x 600");
    }
}