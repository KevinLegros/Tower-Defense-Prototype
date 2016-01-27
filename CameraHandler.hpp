#ifndef _CAMERAHANDLER_HPP_
#define _CAMERAHANDLER_HPP_

#include <SDL.h>

#include "MapArea.hpp"
#include "variables.hpp"

enum {
    TARGETMODE_NORMAL = 0,
    TARGETMODE_CENTER,
    TARGETMODE_FREE
};

class CameraHandler {
    public:
        static CameraHandler cameraControl;

    private:
        int x;
        int y;

        float* targetX;
        float* targetY;

    public:
        int targetMode;

    public:
        CameraHandler();

    public:
        void onMove(int mX, int mY);

    public:
        int getX();
        int getY();

    public:
        void setPos(int x, int y);
        void setTarget(float* x, float* y);
};

#endif
