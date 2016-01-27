#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include <SDL.h>
#include "Globals.hpp"

class EventHandler {
    public:
        EventHandler();

        virtual ~EventHandler();

    public:

        virtual void onEvent(SDL_Event* event);
        virtual void onInputFocus();
        virtual void onInputBlur();
        virtual void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
        virtual void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
        virtual void onMouseFocus();
        virtual void onMouseBlur();
        virtual void onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
        virtual void onLButtonDown(int mX, int mY);
        virtual void onLButtonUp(int mX, int mY);
        virtual void onRButtonDown(int mX, int mY);
        virtual void onRButtonUp(int mX, int mY);
        virtual void onMButtonDown(int mX, int mY);
        virtual void onMButtonUp(int mX, int mY);
        virtual void onMinimize();
        virtual void onRestore();
        virtual void onResize(int w, int h);
        virtual void onExpose();
        virtual void onExit();
        virtual void onUser(Uint8 type, int code, void* data1, void* data2);

};

#endif
