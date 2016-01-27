#include "BuilderButton.hpp"
#include "Game.hpp"

BuilderButton::BuilderButton() {
    buttonImg = NULL;
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    xs = 0;
    ys = 0;
    id = 0;
    initialy = 0;
    hovered = false;
    selected = false;
    clicked = false;
}

BuilderButton::BuilderButton(int id, int x, int y, int w, int h, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    xs = 0;
    ys = 0;
    initialy = 0;
    /*if(strncmp(ext, "bmp", 3) < 1) {
        buttonImg = SpriteLoader::loadBMP(file);
        SpriteLoader::makeTransparent(buttonImg, 0, 138, 118);
    } else*/
    buttonImg = SpriteLoader::loadPNG(file);
}

BuilderButton::BuilderButton(int id, int x, int y, int w, int h, int xs, int ys, char* file) {
    buttonImg = NULL;
    this->id = id;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    this->xs = xs;
    this->ys = ys;
    initialy = ys;
    /*if(strncmp(ext, "bmp", 3) < 1) {
        buttonImg = SpriteLoader::loadBMP(file);
        SpriteLoader::makeTransparent(buttonImg, 0, 138, 118);
        printf("%s made transparent\n", file);
    } else {*/
    buttonImg = SpriteLoader::loadPNG(file);
        /*printf("%s is png\n", file);
    }*/
}

void BuilderButton::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Mouse over
        if((id >= BUILDERBUTTON_EXIT && id <= BUILDERBUTTON_SAVE) && !Left) {
            xs = 40;
            hovered = true;
        } else if(!Left && (id >= TILEBUTTON_NW && id <= TILEBUTTON_CC)) {
            ys = initialy + 3 * 32;
        }
    } else {
        // Mouse not over
        if(id >= BUILDERBUTTON_EXIT && id <= BUILDERBUTTON_SAVE) {
            xs = 0;
            hovered = false;
        } else if(id >= TILEBUTTON_NW && id <= TILEBUTTON_CC){
            ys = initialy;
        }
    }
}

void BuilderButton::onLButtonDown(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button clicked
        if(id >= BUILDERBUTTON_EXIT && id <= BUILDERBUTTON_SAVE) {
            xs = 80;
        }
    }
}

void BuilderButton::onLButtonUp(int mX, int mY) {
    if((mX > box.x) && (mX < box.x + box.w) && (mY > box.y) && (mY < box.y + box.h)) {
        // Button released
        if(id >= BUILDERBUTTON_EXIT && id <= BUILDERBUTTON_SAVE) {
            xs = 40;
            //Game::getInstance()->onExit();
            switch(id) {
                case BUILDERBUTTON_EXIT:
                    GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
                    break;
                case BUILDERBUTTON_LOAD:
                    clicked = true;
                    break;
            }
        } else if(id >= TILEBUTTON_NW && id <= TILEBUTTON_CC) {
            selected = true;
        }
    }
}

void BuilderButton::render(SDL_Surface* screen) {
    SpriteLoader::render(screen, buttonImg, box.x, box.y, xs, ys, box.w, box.h);
    if(selected)
        SpriteLoader::render(screen, buttonImg, box.x, box.y, 4*32, 2*32, 32, 32);
}

void BuilderButton::cleanup() {
    if(buttonImg) {
        SDL_FreeSurface(buttonImg);
        buttonImg = NULL;
    }
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    xs = 0;
    ys = 0;
    id = 0;
    initialy = 0;
    hovered = false;
    selected = false;
}

bool BuilderButton::isHovered() {
    return hovered;
}

bool BuilderButton::isSelected() {
    return selected;
}

bool BuilderButton::isClicked() {
    return clicked;
}
