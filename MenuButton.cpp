#include "MenuButton.hpp"
#include "Game.hpp"

MenuButton::MenuButton() {
    buttonImg = NULL;
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    xs = 0;
    ys = 0;
    id = 0;
}

MenuButton::MenuButton(int id, int x, int y, int w, int h, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xs = 0;
    ys = 0;
    buttonImg = SpriteLoader::loadPNG(file);
}

MenuButton::MenuButton(int id, int x, int y, int w, int h, int xs, int ys, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    this->xs = xs;
    this->ys = ys;
    buttonImg = SpriteLoader::loadPNG(file);
}

void MenuButton::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Mouse over
        if((id == MENUBUTTON_EXIT || id == MENUBUTTON_PLAY || id == MENUBUTTON_BUILDER) && !Left) {
            xs = 40;
        }
    } else {
        // Mouse not over
        if(id == MENUBUTTON_EXIT ||id == MENUBUTTON_PLAY || id == MENUBUTTON_BUILDER) {
            xs = 0;
        }
    }
}

void MenuButton::onLButtonDown(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button clicked
        if(id == MENUBUTTON_EXIT || id == MENUBUTTON_PLAY ||id == MENUBUTTON_BUILDER) {
            xs = 80;
        }
    }
}

void MenuButton::onLButtonUp(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button released
        if(id == MENUBUTTON_EXIT) {
            xs = 40;
            //Game::getInstance()->onExit();
            Globals::setExitClicked(true);
            printf("exitClicked: %i\n", Globals::isExitClicked());
        }
        if(id == MENUBUTTON_PLAY) {
            xs = 40;
            GameStateManager::setActiveGameState(GAMESTATE_PLAY);
        }
        if(id == MENUBUTTON_BUILDER) {
            xs = 40;
            GameStateManager::setActiveGameState(GAMESTATE_BUILDER);
        }
    }
}

void MenuButton::render(SDL_Surface* screen) {
    SpriteLoader::render(screen, buttonImg, box.x, box.y, xs, ys, box.w, box.h);
}

void MenuButton::cleanup() {
    if(buttonImg) {
        SDL_FreeSurface(buttonImg);
        buttonImg = NULL;
    }
}
