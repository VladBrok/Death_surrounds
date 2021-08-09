#include "precompiled.h"
#include "SettingsState.h"
#include "Utils.h"


SettingsState::SettingsState(sf::RenderWindow& window,
                             const std::unordered_map<std::string, sf::Keyboard::Key>& supportedKeys,
                             std::stack<State*>& states
                             )
    : State(window, supportedKeys, states)
{
    stateType = STATE_PROCESSES_EVENTS;

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


void SettingsState::processEvent(const sf::Event& event)
{
    updateMousePosition();

    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        b->second->processEvent(event, mousePosWindow);
    }

    for (auto d = dropDownLists.begin(); d != dropDownLists.end(); ++d)
    {
        d->second->processEvent(event, mousePosWindow);
    }

    // Reacting on the pressed buttons
    if (buttons["APPLY"]->isPressed())
    {
        sf::Vector2u resolution(
            getResolutionFromString(
                dropDownLists["RESOLUTION"]->getActiveElementText()
            )
        );
        window.create(sf::VideoMode(resolution.x, resolution.y), "Death surrounds", sf::Style::Close);

        reinitialize();
    }
    else if (buttons["EXIT_STATE"]->isPressed())
    {
        endActivity();
    }
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
    const sf::Vector2u windowSize(window.getSize());


    /*=============== Buttons ===============*/

    const sf::Vector2f buttonSize(
        static_cast<float>(utils::percentToPixels(14.f, windowSize.x)),
        static_cast<float>(utils::percentToPixels(9.f, windowSize.y))
    );
    const sf::Color textIdleColor(sf::Color(150, 150, 150));
    const sf::Color textHoverColor(sf::Color::White);
    const sf::Color textActiveColor(sf::Color(20, 20, 20, 200));

    buttons["APPLY"] = new Button((float)(int)utils::percentToPixels(50.f, windowSize.x), 
                                  (float)(int)utils::percentToPixels(87.f, windowSize.y), 
                                  buttonSize.x,
                                  buttonSize.y, 
                                  font, 
                                  "Apply",
                                  textIdleColor,
                                  textHoverColor,
                                  textActiveColor
                                  );

    buttons["EXIT_STATE"] = new Button((float)(int)utils::percentToPixels(83.f, windowSize.x), 
                                       (float)(int)utils::percentToPixels(87.f, windowSize.y), 
                                       buttonSize.x,
                                       buttonSize.y, 
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

        /*
            Note: this "((window.getSize().y % 10) ? 13: 0" statement below is used,
            because when the window height value has the non-zero last number,
            it cuts down the actual height of the window on 13 pixels 
            (i don't know why this happens, it's really strange).
        */
        if (videoModes[i].width == window.getSize().x &&
            videoModes[i].height == window.getSize().y + ((window.getSize().y % 10) ? 13: 0))
        {
            activeResolutionIndex = i;
        }
    }

    dropDownLists["RESOLUTION"] = 
        new DropDownList(
             (float)(int)utils::percentToPixels(22.f, windowSize.x), 
             (float)(int)utils::percentToPixels(50.f, windowSize.y), 
             utils::percentToPixels(14.6f, windowSize.x), 
             utils::percentToPixels(6.5f, windowSize.y), 
             font, 
             resolutions, 
             activeResolutionIndex
        );
}


void SettingsState::initBackground()
{
    background.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    background.setTexture(&textures.at("BACKGROUND"));
}


void SettingsState::initTextures()
{
    textures["BACKGROUND"].loadFromFile("Resources\\Images\\Backgrounds\\main_menu_bg.png");
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


void SettingsState::reinitialize()
{
    for (auto b = buttons.begin(); b != buttons.end(); ++b)
    {
        delete b->second;
    }    
    buttons.clear();

    for (auto d = dropDownLists.begin(); d != dropDownLists.end(); ++d)
    {
        delete d->second;
    } 
    dropDownLists.clear();

    initGui();
    initBackground();
}