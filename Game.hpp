#ifndef _GAME_HPP_
#define _GAPE_HPP_

#include <SDL.h>
#include "SDL_ttf.h"

#include "EventHandler.hpp"
#include "SpriteLoader.hpp"
#include "GameStateManager.hpp"

class Game : public EventHandler {
    public:
        static Game* getInstance();
        static Game instance;

    public:
        bool running;
        SDL_Surface* screen;
        int FPS;
        int gameFps;
        int lastCurTime;
        int lastTime;
        int lastTimeSF;

    public:
        Game();

    public:
        int startGame();
        bool initGame();

    public:
        void eventTriggered(SDL_Event* event);
            void onExit();
        void update();
        void render();
        void cleanup();
};

#endif
