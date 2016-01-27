#include "Tower.hpp"

Tower::Tower() {
}

bool Tower::load(char* file, int w, int h, int maxFrames) {
    if(Entity::load(file, w, h, maxFrames, id) == false) return false;

    return true;
}

void Tower::update() {
    Entity::update();
}

void Tower::render(SDL_Surface* screen) {
    Entity::render(screen);
}

void Tower::cleanup() {
    Entity::cleanup();
}

void Tower::animate() {
    if(speedX != 0) animControl.maxFrames = 1;
    else animControl.maxFrames = 0;

    Entity::animate();
}

bool Tower::handleCollision(Entity* entity) {
    return true;
}
