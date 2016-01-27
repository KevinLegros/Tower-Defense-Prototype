#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include "Entity.hpp"

class Player : public Entity {
    public:
        Player();

        bool load(char* file, int w, int h, int maxFrames);
        void update();
        void render(SDL_Surface* screen);
        void cleanup();
        void animate();
        bool handleCollision(Entity* entity);
};

#endif
