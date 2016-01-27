#include "Enemy.hpp"

Enemy::Enemy() {
}

bool Enemy::load(char* file, int w, int h, int maxFrames, int id) {
    if(Entity::load(file, w, h, maxFrames, id) == false) return false;

    return true;
}

void Enemy::update() {
    Entity::update();
}

void Enemy::render(SDL_Surface* screen) {
    Entity::render(screen);
}

void Enemy::cleanup() {
    Entity::cleanup();
}

void Enemy::animate() {
    if(speedX != 0) animControl.maxFrames = 0;
    else animControl.maxFrames = 0;

    Entity::animate();
}

bool Enemy::handleCollision(Entity* entity) {
    return true;
}
