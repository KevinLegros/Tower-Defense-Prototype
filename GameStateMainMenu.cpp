#include "GameStateMainMenu.hpp"
#include "GameStateManager.hpp"

GameStateMainMenu GameStateMainMenu::instance;

GameStateMainMenu::GameStateMainMenu() {
    backgroundMenu = NULL;
}

void GameStateMainMenu::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    for(int i = 0; i < menuButtons.size(); i++) {
        menuButtons[i]->onMouseMove(mX, mY, relX, relY, Left, Right, Middle);
    }
}

void GameStateMainMenu::onLButtonDown(int mX, int mY) {
    for(int i = 0; i < menuButtons.size(); i++) {
        menuButtons[i]->onLButtonDown(mX, mY);
    }
}

void GameStateMainMenu::onLButtonUp(int mX, int mY) {
    for(int i = 0; i < menuButtons.size(); i++) {
        if(!menuButtons[i]) continue;
        menuButtons[i]->onLButtonUp(mX, mY);
    }
}

void GameStateMainMenu::onActivate() {
    char fileBuffer[100] = {0};
    sprintf(fileBuffer, "%smenu_ph.png", RESSOURCEDIR);
    backgroundMenu = SpriteLoader::loadPNG(fileBuffer);

    sprintf(fileBuffer, "%sPlay.png", RESSOURCEDIR);
    menuButtons.push_back(new MenuButton(MenuButton::MENUBUTTON_PLAY, WWIDTH/2 - 40/2, WHEIGHT/2 - 45, 40, 30, 0, 0, fileBuffer));
    sprintf(fileBuffer, "%sBuilder.png", RESSOURCEDIR);
    menuButtons.push_back(new MenuButton(MenuButton::MENUBUTTON_BUILDER, WWIDTH/2 - 40/2, WHEIGHT/2, 40, 30, 0, 0, fileBuffer));
    sprintf(fileBuffer, "%sExit.png", RESSOURCEDIR);
    menuButtons.push_back(new MenuButton(MenuButton::MENUBUTTON_EXIT, WWIDTH/2 - 40/2, WHEIGHT/2 + 45, 40, 30, 0, 0, fileBuffer));
    //delete fileBuffer;
}

void GameStateMainMenu::onDeactivate() {
    for(int i = 0; i < menuButtons.size(); i++) {
        menuButtons[i]->cleanup();
        delete menuButtons[i];
        menuButtons[i] = NULL;
    }
    menuButtons.clear();
    if(backgroundMenu) {
        SDL_FreeSurface(backgroundMenu);
        backgroundMenu = NULL;
    }
}

void GameStateMainMenu::update() {
}

void GameStateMainMenu::render(SDL_Surface* screen) {
    if(backgroundMenu) {
        SpriteLoader::render(screen, backgroundMenu, 0, 0);
    }
    for(int i = 0; i < menuButtons.size(); i++) {
        menuButtons[i]->render(screen);
    }
}

GameStateMainMenu* GameStateMainMenu::getInstance() {
    return &instance;
}
