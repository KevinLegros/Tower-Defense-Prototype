#include "DialogButton.hpp"
#include "Game.hpp"

DialogButton::DialogButton() {
    buttonImg = NULL;
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    xs = 0;
    ys = 0;
    id = 0;
    clicked = false;
}

DialogButton::DialogButton(int id, int x, int y, int w, int h, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xs = 0;
    ys = 0;
    clicked = false;
    buttonImg = SpriteLoader::loadPNG(file);
}

DialogButton::DialogButton(int id, int x, int y, int w, int h, int xs, int ys, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    this->xs = xs;
    this->ys = ys;
    clicked = false;
    buttonImg = SpriteLoader::loadPNG(file);
}

void DialogButton::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Mouse over
        xs = 40;
    } else {
        // Mouse not over
        xs = 0;
    }
}

void DialogButton::onLButtonDown(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button clicked
        xs = 80;
    }
}

void DialogButton::onLButtonUp(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button released
        xs = 40;
        clicked = true;
    }
}

void DialogButton::render(SDL_Surface* screen) {
    SpriteLoader::render(screen, buttonImg, box.x, box.y, xs, ys, box.w, box.h);
}

void DialogButton::cleanup() {
    if(buttonImg) {
        SDL_FreeSurface(buttonImg);
        buttonImg = NULL;
    }
}
