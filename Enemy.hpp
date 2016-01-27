#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include "Entity.hpp"

class Enemy : public Entity {
    public:
        Enemy();

        bool load(char* file, int w, int h, int maxFrames, int id);
        void update();
        void render(SDL_Surface* screen);
        void cleanup();
        void animate();
        bool handleCollision(Entity* entity);
};

#endif
