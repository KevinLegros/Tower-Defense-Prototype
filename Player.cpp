#include "Player.hpp"

Player::Player() {
}

bool Player::load(char* file, int w, int h, int maxFrames) {
    if(Entity::load(file, w, h, maxFrames, id) == false) return false;

    return true;
}

void Player::update() {
    Entity::update();

    if(x < WWIDTH / 2) x = WWIDTH / 2;
    if(x + (WWIDTH / 2) > MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize) x = MAP_WIDTH * TILE_SIZE * MapArea::areaControl.areaSize - WWIDTH / 2;
    if(y < WHEIGHT / 2) y = WHEIGHT / 2;
    if(y + (WHEIGHT / 2) > MAP_HEIGHT * TILE_SIZE * MapArea::areaControl.areaSize) y = MAP_HEIGHT * TILE_SIZE * MapArea::areaControl.areaSize - WHEIGHT / 2;
}

void Player::render(SDL_Surface* screen) {
    Entity::render(screen);
}

void Player::cleanup() {
    Entity::cleanup();
}

void Player::animate() {
    if(speedX != 0) animControl.maxFrames = 0;
    else animControl.maxFrames = 0;

    Entity::animate();
}

bool Player::handleCollision(Entity* entity) {
    return true;
}
