#include "precompiled.h"
#include "Resources.h"


namespace resources
{


    const std::string fontsDirectory       = "Resources\\Fonts\\";
    const std::string tilemapsDirectory    = "Resources\\Maps\\";
    const std::string shadersDirectory     = "Resources\\Shaders\\";
    const std::string backgroundsDirectory = "Resources\\Images\\Backgrounds\\";
    const std::string enemiesDirectory     = "Resources\\Images\\Entities\\Enemies\\";
    const std::string playerDirectory      = "Resources\\Images\\Entities\\Player\\";
    const std::string itemsDirectory       = "Resources\\Images\\Items\\";
    const std::string tilesDirectory       = "Resources\\Images\\Tiles\\";
    const std::string configDirectory      = "Config\\";


    std::string getFontFile()
    {
        return fontsDirectory + "Dosis-Light.ttf";
    }


    std::string getPixelFontFile()
    {
        return fontsDirectory + "PixellettersFull.ttf";
    }


    std::string getTilemapFile()
    {
        return tilemapsDirectory + "tilemap";
    }


    std::string getFragmentShaderFile()
    {
        return shadersDirectory + "fragment_shader.frag";
    }


    std::string getVertexShaderFile()
    {
        return shadersDirectory + "vertex_shader.vert";
    }


    std::string getMainMenuBackgroundFile()
    {
        return backgroundsDirectory + "main_menu_bg.png";
    }


    std::string getRatTextureFile()
    {
        return enemiesDirectory + "rat_60x64.png";
    }


    std::string getSpiderTextureFile()
    {
        return enemiesDirectory + "spider_60x64.png";
    }


    std::string getSkeletonTextureFile()
    {
        return enemiesDirectory + "skeleton_64x64.png";
    }


    std::string getReaperTextureFile()
    {
        return enemiesDirectory + "reaper_39x48.png";
    }


    std::string getVortexTextureFile()
    {
        return enemiesDirectory + "vortex.png";
    }


    std::string getPlayerTextureFile()
    {
        return playerDirectory + "player_sheet.png";
    }


    std::string getPlayerHpBarTextureFile()
    {
        return playerDirectory + "hpbar.png";
    }


    std::string getPlayerExpBarTextureFile()
    {
        return playerDirectory + "expbar.png";
    }


    std::string getSwordTextureFile()
    {
        return itemsDirectory + "sword.png";
    }


    std::string getStaffTextureFile()
    {
        return itemsDirectory + "staff.png";
    }


    std::string getUnloadedStaffTextureFile()
    {
        return itemsDirectory + "unloaded_staff.png";
    }


    std::string getStaffOrbTextureFile()
    {
        return playerDirectory + "staff_orb.png";
    }


    std::string getFoodTextureFile()
    {
        return itemsDirectory + "food.png";
    }


    std::string getInventoryPanelTextureFile()
    {
        return itemsDirectory + "inventory_border.png";
    }


    std::string getTilesheetFile()
    {
        return tilesDirectory + "tilesheet.png";
    }


    std::string getGameStateKeybindsFile()
    {
        return configDirectory + "gamestate_keybinds.ini";
    }


    std::string getEditorStateKeybindsFile()
    {
        return configDirectory + "editorstate_keybinds.ini";
    }


    std::string getSupportedKeysFile()
    {
        return configDirectory + "supported_keys.ini";
    }


} // namespace resources
