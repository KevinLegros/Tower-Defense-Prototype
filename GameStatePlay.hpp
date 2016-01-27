#ifndef _GAMESTATEPLAY_HPP_
#define _GAMESTATEPLAY_HPP_

#include <string>
#include <iostream>

#include "GameState.hpp"
#include "MapArea.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "SpriteLoader.hpp"

class GameStatePlay : public GameState {
    public:
        static GameStatePlay instance;
        Player player;
        Enemy enemy;
        Enemy enemy2;
        bool cameraMoving;
        int mouseposX;
        int mouseposY;

    private:
        GameStatePlay();
        std::vector<SDL_Surface*> debugMessages;

    public:
        void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        void onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle);
        void onLButtonUp(int mx, int my);
        void onRButtonUp(int mx, int my);

    public:
        void onActivate();
        void onDeactivate();
        void update();
        void render(SDL_Surface* screen);

    private:
        void pathfinding(Entity* e);

    public:
        static GameStatePlay* getInstance();
};

#endif
