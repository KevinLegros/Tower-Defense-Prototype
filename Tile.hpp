#ifndef _TILE_HPP_
#define _TILE_HPP_

#include "variables.hpp"


class Tile {
    public:
        int tileID;
        int spriteID;
        int typeID;
        int x;
        int y;
        bool hovered;
        bool selected;
        enum {
            TILETYPE_NONE = 0,
            TILETYPE_NORMAL,
            TILETYPE_BLOCK
        };

    public:
        Tile();
};

#endif
