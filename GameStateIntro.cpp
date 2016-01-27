#include "GameStateIntro.hpp"
#include "GameStateManager.hpp"

GameStateIntro GameStateIntro::instance;

GameStateIntro::GameStateIntro() {
    logoImg = NULL;
}

void GameStateIntro::onActivate() {
    char fileBuffer[100] = {0};
    sprintf(fileBuffer, "%ssplash.png", RESSOURCEDIR);
    logoImg = SpriteLoader::loadPNG(fileBuffer);
    delete fileBuffer;
    startTime = SDL_GetTicks();
}

void GameStateIntro::onDeactivate() {
    if(logoImg) {
        SDL_FreeSurface(logoImg);
        logoImg = NULL;
    }
}

void GameStateIntro::update() {
    if(startTime + 3000 < SDL_GetTicks()) {
        GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
    }
}

void GameStateIntro::render(SDL_Surface* screen) {
    if(logoImg) {
        SpriteLoader::render(screen, logoImg, 0, 0);
    }
}

void GameStateIntro::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_ESCAPE:
            GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
            break;
        case SDLK_RETURN:
            GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
            break;
        case SDLK_SPACE:
            GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
            break;
        default:
            break;
    }
}

GameStateIntro* GameStateIntro::getInstance() {
    return &instance;
}
