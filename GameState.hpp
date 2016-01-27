#ifndef _GAMESTATE_HPP_
#define _GAMESTATE_HPP_

#include "EventHandler.hpp"
#include "variables.hpp"

class GameState : public EventHandler {
    public:
        GameState();

    public:
        virtual void onActivate() = 0;
        virtual void onDeactivate() = 0;
        virtual void update() = 0;
        virtual void render(SDL_Surface* screen) = 0;
};

#endif
