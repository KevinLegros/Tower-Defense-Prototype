#ifndef _MAPAREA_HPP_
#define _MAPAREA_HPP_

#include "TileMap.hpp"

class MapArea {
    public:
        static MapArea areaControl;

    public:
        std::vector<TileMap> mapsInArea;
        int areaSize;   // Square area
        int tileHover;
        int tileSelected;

    private:
        SDL_Surface* tilesetSprite;

    public:
        MapArea();

        bool load(char* file);
        void render(SDL_Surface* screen, int camx, int camy);
        void cleanup();

    public:
        TileMap* getMapAt(int x, int y);
        TileMap* getMapId(int id);
        Tile* getTileAt(int x, int y);
        Tile* getTileId(int id);
        int getTileHoveredId();
};

#endif
