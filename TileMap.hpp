#ifndef _TILEMAP_HPP_
#define _TILEMAP_HPP_

#include <SDL.h>
#include <vector>

#include "Tile.hpp"
#include "SpriteLoader.hpp"

class TileMap {
    public:
        SDL_Surface* tilesetSprite;
        int mapId;

    public:
        std::vector<Tile> tileList;

    public:
        TileMap();

    public:
        bool load(char* file, int mapid);
        void render(SDL_Surface* screen, int mapX, int mapY);

    public:
        Tile* getTileAt(int x, int y);
        Tile* getTileId(int id);
        std::vector<Tile>* getTileList();
};

#endif
