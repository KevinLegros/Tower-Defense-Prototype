#include "AnimationHandler.hpp"

AnimationHandler::AnimationHandler() {
    curFrame = 0;
    maxFrames = 0;
    frameIncr = 1;       // 1 = increase, -1 = decrease

    frameRate = 60;
    oldTime = 0;

    oscillate = false;  // Allows to : 01234543210123...
}

void AnimationHandler::animate() {
    if(oldTime + frameRate > SDL_GetTicks()) return;

    oldTime = SDL_GetTicks();
    curFrame += frameIncr;

    if(oscillate) {
        if(frameIncr > 0) {
            if(curFrame >= maxFrames) {
                frameIncr = -frameIncr;
            }
        } else {
            if(curFrame <= 0) {
                frameIncr = -frameIncr;
            }
        }
    } else {
        if(curFrame >= maxFrames) {
            curFrame = 0;
        }
    }
}

void AnimationHandler::setFrameRate(int rate) {
    frameRate = rate;
}

void AnimationHandler::setCurFrame(int frame) {
    if(frame < 0 || frame >= maxFrames) return;

    curFrame = frame;
}

int AnimationHandler::getCurFrame() {
    return curFrame;
}
