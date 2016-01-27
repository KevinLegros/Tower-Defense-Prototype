#ifndef _MENUBUTTON_HPP_
#define _MENUBUTTON_HPP_

#include "EventHandler.hpp"
#include "SpriteLoader.hpp"


class MenuButton : public EventHandler {
    private:
        SDL_Rect box;
        SDL_Surface* buttonImg;
        int xs;
        int ys;
        int id;

    public:
        enum {
            MENUBUTTON_UNDEF = 0,
            MENUBUTTON_PLAY,
            MENUBUTTON_BUILDER,
            MENUBUTTON_EXIT
        };

    public:
        MenuButton();
        MenuButton(int id, int x, int y, int w, int h, char* file);
        MenuButton(int id, int x, int y, int w, int h, int xs, int ys, char* file);

    public:
        void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
        void onLButtonDown(int mX, int mY);
        void onLButtonUp(int mX, int mY);

    public:
        void render(SDL_Surface* screen);
        void cleanup();
};

#endif
