#ifndef _ANIMATIONHANDLER_HPP_
#define _ANIMATIONHANDLER_HPP_

#include <SDL.h>

class AnimationHandler {
    private:
        int curFrame;
        int frameIncr;

    private:
        int frameRate;  // in ms
        long oldTime;

    public:
        int maxFrames;
        bool oscillate;

    public:
        AnimationHandler();
        void animate();

    public:
        void setFrameRate(int rate);
        void setCurFrame(int frame);
        int getCurFrame();
};

#endif
