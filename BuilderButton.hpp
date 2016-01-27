#ifndef _BUILDERBUTTON_HPP_
#define _BUILDERBUTTON_HPP_

#include "EventHandler.hpp"
#include "SpriteLoader.hpp"

enum {
    TILEBUTTON_NW = 100,
    TILEBUTTON_N,
    TILEBUTTON_NE,
    TILEBUTTON_BNW,
    TILEBUTTON_BNE,
    TILEBUTTON_W,
    TILEBUTTON_C,
    TILEBUTTON_E,
    TILEBUTTON_BSW,
    TILEBUTTON_BSE,
    TILEBUTTON_SW,
    TILEBUTTON_S,
    TILEBUTTON_SE,
    TILEBUTTON_CC
};

class BuilderButton : public EventHandler {
    private:
        SDL_Rect box;
        SDL_Surface* buttonImg;
        int xs;
        int ys;
        int initialy;

    public:
        int id;
        bool hovered;
        bool selected;
        bool clicked;
        enum {
            BUILDERBUTTON_UNDEF = 0,
            BUILDERBUTTON_EXIT,
            BUILDERBUTTON_LOAD,
            BUILDERBUTTON_SAVE
        };

    public:
        BuilderButton();
        BuilderButton(int id, int x, int y, int w, int h, char* file);
        BuilderButton(int id, int x, int y, int w, int h, int xs, int ys, char* file);

    public:
        void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
        void onLButtonDown(int mX, int mY);
        void onLButtonUp(int mX, int mY);

    public:
        void render(SDL_Surface* screen);
        void cleanup();

    public:
        bool isHovered();
        bool isSelected();
        bool isClicked();
};

#endif
