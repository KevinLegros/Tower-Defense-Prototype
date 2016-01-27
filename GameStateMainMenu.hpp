#ifndef _GAMESTATEMAINMENU_HPP_
#define _GAMESTATEMAINMENU_HPP_

#include <vector>

#include "GameState.hpp"
#include "SpriteLoader.hpp"
#include "MenuButton.hpp"

class GameStateMainMenu : public GameState {
    private:
        static GameStateMainMenu instance;
        SDL_Surface* backgroundMenu;
        std::vector<MenuButton*> menuButtons;

    private:
        GameStateMainMenu();

    public:
        void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
        void onLButtonDown(int mX, int mY);
        void onLButtonUp(int mX, int mY);

    public:
        void onActivate();
        void onDeactivate();
        void update();
        void render(SDL_Surface* screen);

    public:
        static GameStateMainMenu* getInstance();
};

#endif
