#ifndef _DIALOGBUTTON_HPP_
#define _DIALOGBUTTON_HPP_

#include "EventHandler.hpp"
#include "SpriteLoader.hpp"


class DialogButton : public EventHandler {
    private:
        SDL_Rect box;
        SDL_Surface* buttonImg;
        int xs;
        int ys;
        int id;
        bool clicked;

    public:
        enum {
            DIALOGBUTTON_OK = 1,
            DIALOGBUTTON_CANCEL,
            DIALOGBUTTON_YES,
            DIALOGBUTTON_NO
        };

    public:
        DialogButton();
        DialogButton(int id, int x, int y, int w, int h, char* file);
        DialogButton(int id, int x, int y, int w, int h, int xs, int ys, char* file);

    public:
        void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
        void onLButtonDown(int mX, int mY);
        void onLButtonUp(int mX, int mY);

    public:
        void render(SDL_Surface* screen);
        void cleanup();
};

#endif
