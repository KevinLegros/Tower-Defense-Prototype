#ifndef _DIALOGBOX_HPP_
#define _DIALOGBOX_HPP_

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <vector>

#include "EventHandler.hpp"
#include "SpriteLoader.hpp"
#include "variables.hpp"
#include "DialogButton.hpp"

class DialogBox {
    public:
        int x;
        int y;
        int w;
        int h;
        int buttons;
        bool visible;
        bool hovered;
        SDL_Surface* sprite;
        std::vector<std::string> mapsInFolder;
        enum {
            OK = 1,
            OK_CANCEL,
            YES,
            YES_NO
        };
        std::vector<DialogButton*> dialogButtons;

    public:
        DialogBox();
        DialogBox(int x, int y, int w, int h, int buttons);

    public:
        void onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle);

    public:
        void update();
        void render(SDL_Surface* screen);
        void cleanup();

    public:
        void listFiles();
};

#endif
