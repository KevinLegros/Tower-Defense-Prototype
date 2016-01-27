#ifndef _GAMESTATEBUILDER_HPP_
#define _GAMESTATEBUILDER_HPP_

#include <vector>

#include "GameState.hpp"
#include "BuilderButton.hpp"
#include "DialogBox.hpp"
#include "MapArea.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "SpriteLoader.hpp"

class GameStateBuilder : public GameState {
    public:
        static GameStateBuilder instance;
        Player player;
        bool cameraMoving;

        SDL_Surface* BuilderUI;

        std::vector<BuilderButton*> tileButtons;
        std::vector<BuilderButton*> builderButtons;

        DialogBox* dialogBox;

        SDL_Surface* message;

        std::vector<SDL_Surface*> mapsNames;

        int currentTile;
        int oldTile;

    private:
        GameStateBuilder();

    public:
        void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        void onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle);
        void onLButtonDown(int mx, int my);
        void onLButtonUp(int mx, int my);
        void onRButtonUp(int mx, int my);

    public:
        void onActivate();
        void onDeactivate();
        void update();
        void render(SDL_Surface* screen);

    public:
        void loadLevel(char* area);
        void saveLevel();

    public:
        static GameStateBuilder* getInstance();
};

#endif
