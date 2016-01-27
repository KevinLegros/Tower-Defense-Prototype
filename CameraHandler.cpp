#include "CameraHandler.hpp"

CameraHandler CameraHandler::cameraControl;

CameraHandler::CameraHandler() {
    x = y = 0;
    targetX = targetY = NULL;
    targetMode = TARGETMODE_NORMAL;
}

void CameraHandler::onMove(int mX, int mY) {
    x += mX;
    y += mY;
}

int CameraHandler::getX() {
    if(targetX != NULL) {
        if(targetMode == TARGETMODE_CENTER) {
            if(*targetX - (WWIDTH / 2) < 0) return 0;
            if(*targetX + (WWIDTH / 2) > MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize) return MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize - WWIDTH;
            return *targetX - (WWIDTH / 2);
        }

        if(*targetX < 0) return 0;
        return *targetX;
    }
    return x;
}

int CameraHandler::getY() {
    if(targetY != NULL) {
        if(targetMode == TARGETMODE_CENTER) {
            if(*targetY - (WHEIGHT / 2) < 0) return 0;
            if(*targetY + (WHEIGHT / 2) > MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize) return MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize - WHEIGHT;
            return *targetY - (WHEIGHT/ 2);
        }

        if(*targetY < 0) return 0;
        return *targetY;
    }
    return y;
}

void CameraHandler::setPos(int x, int y) {
    this->x = x;
    this->y = y;
}

void CameraHandler::setTarget(float* x, float* y) {
    targetX = x;
    targetY = y;
}
