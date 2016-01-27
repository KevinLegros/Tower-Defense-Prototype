#include "MapArea.hpp"

MapArea MapArea::areaControl;

MapArea::MapArea() {
    areaSize = 0;
    tileHover = -1;
    tileSelected = -1;
}

bool MapArea::load(char* file) {
    mapsInArea.clear();

    FILE* fileHandle = fopen(file, "r");

    if(fileHandle == NULL) return false;

    char tilesetFile[255];

    fscanf(fileHandle, "%s\n", tilesetFile);

    if((tilesetSprite = SpriteLoader::loadPNG(tilesetFile)) == false) {
        fclose(fileHandle);
        return false;
    }

    fscanf(fileHandle, "%d\n", &areaSize);

    int i = 0;

    for(int x = 0; x < areaSize; x++) {
        for(int y = 0; y < areaSize; y++) {
            char mapFile[255];

            fscanf(fileHandle, "%s ", mapFile);

            TileMap tempMap;
            if(tempMap.load(mapFile, i) == false) {
                fclose(fileHandle);
                return false;
            }

            tempMap.tilesetSprite = tilesetSprite;
            mapsInArea.push_back(tempMap);

            i++;
        }
        fscanf(fileHandle, "\n");
    }

    fclose(fileHandle);

    return true;
}

void MapArea::render(SDL_Surface* screen, int camx, int camy) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;

    int firstId = -camx / mapWidth;
    firstId = firstId + ((-camy / mapHeight) * areaSize);

    // Can only see 4 maps max on screen for 640*480
    // Same for 800 * 600
    for(int i = 0; i < 4; i++) {
        int id = firstId + ((i / 2) * areaSize) + (i % 2);

        if(id < 0 || id >= mapsInArea.size()) continue;

        int x = ((id % areaSize) * mapWidth) + camx;
        int y = ((id / areaSize) * mapHeight) + camy;

        mapsInArea[id].render(screen, x, y);
    }
}

void MapArea::cleanup() {
    if(tilesetSprite) {
        SDL_FreeSurface(tilesetSprite);
    }

    mapsInArea.clear();

    tileHover = -1;
    tileSelected = -1;
}

TileMap* MapArea::getMapAt(int x, int y) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;

    int id = x / mapWidth;
    id = id + ((y / mapHeight) * areaSize);

    if(id < 0 || id >= mapsInArea.size()) return NULL;

    return &mapsInArea[id];
}

TileMap* MapArea::getMapId(int id) {
    for(int i = 0; i < mapsInArea.size(); i++) {
        if(mapsInArea[i].mapId == id) return &mapsInArea[id];
    }
    return NULL;
}

Tile* MapArea::getTileAt(int x, int y) {
    int mapWidth = MAP_WIDTH * TILE_SIZE;
    int mapHeight = MAP_HEIGHT * TILE_SIZE;

    TileMap* map = getMapAt(x, y);

    if(map == NULL) return NULL;

    x = x % mapWidth;
    y = y % mapHeight;

    return map->getTileAt(x, y);
}

Tile* MapArea::getTileId(int id) {
    Tile* hovered = NULL;
    int mapid = id / (MAP_WIDTH * MAP_HEIGHT);
    hovered = &mapsInArea[mapid].tileList[id - (mapid * (MAP_WIDTH * MAP_HEIGHT))];
    return hovered;
}

int MapArea::getTileHoveredId() {
    return tileHover;
}
