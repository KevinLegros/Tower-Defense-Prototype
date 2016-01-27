#ifndef _GAMESTATEINTRO_HPP_
#define _GAMESTATEINTRO_HPP_

#include "GameState.hpp"
#include "SpriteLoader.hpp"
#include "variables.hpp"

class GameStateIntro : public GameState {
    private:
        static GameStateIntro instance;
        SDL_Surface* logoImg;
        int startTime;

    private:
        GameStateIntro();

    public:
        void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

    public:
        void onActivate();
        void onDeactivate();
        void update();
        void render(SDL_Surface* screen);

    public:
        static GameStateIntro* getInstance();
};

#endif
