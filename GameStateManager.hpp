#ifndef _GAMESTATEMANAGER_HPP_
#define _GAMESTATEMANAGER_HPP_

#include "GameState.hpp"

enum {
    GAMESTATE_NONE,
    GAMESTATE_INTRO,
    GAMESTATE_MAINMENU,
    GAMESTATE_PLAY,
    GAMESTATE_BUILDER
};

class GameStateManager {
    private:
        static GameState* activeGameState;

    public:
        static void onEvent(SDL_Event* Event);
        static void update();
        static void render(SDL_Surface* screen);

    public:
        static void setActiveGameState(int gameStateID);
        static GameState* getActiveGameState();
};

#endif
