#ifndef _TOWER_HPP_
#define _TOWER_HPP_

#include "Entity.hpp"

class Tower : public Entity{
    public:
        Tower();

    public:
        bool load(char* file, int w, int h, int maxFrames);
        void update();
        void render(SDL_Surface* screen);
        void cleanup();
        void animate();
        bool handleCollision(Entity* entity);
};

#endif
