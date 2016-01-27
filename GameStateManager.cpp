#include "GameStateManager.hpp"

#include "GameStateIntro.hpp"
#include "GameStateMainMenu.hpp"
#include "GameStatePlay.hpp"
#include "GameStateBuilder.hpp"

GameState* GameStateManager::activeGameState = 0;

void GameStateManager::onEvent(SDL_Event* eventHolder) {
    if(activeGameState) activeGameState->onEvent(eventHolder);
}

void GameStateManager::update() {
    if(activeGameState) activeGameState->update();
}

void GameStateManager::render(SDL_Surface* screen) {
    if(activeGameState) activeGameState->render(screen);
}

void GameStateManager::setActiveGameState(int gameStateId) {
    if(activeGameState) activeGameState->onDeactivate();

    if(gameStateId == GAMESTATE_NONE) activeGameState = 0;
    if(gameStateId == GAMESTATE_INTRO) activeGameState = GameStateIntro::getInstance();
    if(gameStateId == GAMESTATE_MAINMENU) activeGameState = GameStateMainMenu::getInstance();
    if(gameStateId == GAMESTATE_PLAY) activeGameState = GameStatePlay::getInstance();
    if(gameStateId == GAMESTATE_BUILDER) activeGameState = GameStateBuilder::getInstance();

    if(activeGameState) activeGameState->onActivate();
}

GameState* GameStateManager::getActiveGameState() {
    return activeGameState;
}
