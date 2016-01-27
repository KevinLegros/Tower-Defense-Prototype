#ifndef _ENTITY_HPP_
#define _ENTITY_HPP_

#include <vector>

#include "MapArea.hpp"
#include "AnimationHandler.hpp"
#include "CameraHandler.hpp"
#include "SpriteLoader.hpp"
#include "Globals.hpp"
#include "Tile.hpp"

enum {
    ENTITYFLAG_NONE = 0,
    ENTITYFLAG_GRAVITY = 0x00000001,       // Gravity
    ENTITYFLAG_GHOST = 0x00000002,         // Goes through walls
    ENTITYFLAG_MAPONLY = 0x00000004,       // Collides with map only
    ENTITYFLAG_XY = 0x00000008
};
    /*
        Check for multiple flags: Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_GHOST;
        Check for only one flag : if(Flags & ENTITY_FLAG_MAPONLY)
    */

enum {
    ORIENTATION_N = 0,
    ORIENTATION_NE,
    ORIENTATION_E,
    ORIENTATION_SE,
    ORIENTATION_S,
    ORIENTATION_SW,
    ORIENTATION_W,
    ORIENTATION_NW
};

class Entity {
    public:
        static std::vector<Entity*> entityList;
        enum {
            ENTITYTYPE_GENERIC = 0,
            ENTITYTYPE_PLAYER,
            ENTITYTYPE_ENEMY
        };
        Tile* curTile;
        Tile* nextTile;
        int scanned[MAP_WIDTH][MAP_HEIGHT];
        int path[MAP_WIDTH][MAP_HEIGHT];
        bool nextReached;

    protected:
        AnimationHandler animControl;
        SDL_Surface* entitySprite;

    public:
        float x;
        float y;
        int w;
        int h;
        int orientation;
        int id;

        bool moveLeft;
        bool moveRight;
        bool moveUp;
        bool moveDown;
        int turnTime;

    public:
        int type;
        bool dead;
        int flags;

    protected:
        float speedX;
        float speedY;
        float accelX;
        float accelY;

    public:
        float maxSpeedX;
        float maxSpeedY;

    protected:
        int curFrameCol;
        int curFrameRow;

    protected:
        int colx;
        int coly;
        int colw;
        int colh;

    public:
        Entity();
        virtual ~Entity();

    public:
        virtual bool load(char* file, int w, int h, int maxFrames, int id);
        virtual bool loadBMP(char* file, int w, int h, int maxFrames, int id);
        virtual void update();
        virtual void render(SDL_Surface* screen);
        virtual void cleanup();
        virtual void animate();                                                   // defines animation states
        virtual bool handleCollision(Entity* entity);                             // called when collide

    public:
        void onMove(float mx, float my);                                      // accelerate to max speed
        void stopMoveX();
        void stopMoveY();                                                           // deccelerate to 0

    public:
        bool collides(int ox, int oy, int ow, int oh);                              // collision check

    private:
        bool posValid(int nx, int ny);                                          // handles position methods bellow
        bool posValidTile(Tile* tile);                                             // determine if tile is valid
        bool posValidEntity(Entity* entity, int nx, int ny);                   // determine if entity is valid

    public:
        void setSpeedX(float speedX);
        void setSpeedY(float speedY);
};

class CollisionHandler {
    public:
        static std::vector<CollisionHandler> entityColQueue;                               // collision queue

    public:
        Entity* entityA;
        Entity* entityB;

    public:
        CollisionHandler();
};

#endif
