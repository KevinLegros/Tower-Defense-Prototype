#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_

#include "SDL_ttf.h"

class Globals {
    private:
        static bool exitClicked;
        static float speedFactor;
        static TTF_Font* font;

    public:
        Globals();

    public:
        static bool isExitClicked();
        static float getSpeedFactor();
        static TTF_Font* getFont();

    public:
        static void setExitClicked(bool clicked);
        static void setSpeedFactor(float sf);
        static void setFont(TTF_Font *afont);
};

#endif
