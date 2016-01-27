#include "TileMap.hpp"

TileMap::TileMap() {
    mapId = -1;
    tilesetSprite = NULL;
}

bool TileMap::load(char* file, int mapid) {
    // Clear old tiles
    tileList.clear();
    mapId = mapid;

    // Open a filehandle to open the map file
    FILE* fileHandle = fopen(file, "r");

    if(fileHandle == NULL) return false;

    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            Tile tempTile;
            tempTile.tileID = x + y * MAP_WIDTH + (MAP_WIDTH * MAP_HEIGHT * mapid);
            tempTile.x = x + (MAP_WIDTH * MAP_HEIGHT * mapid);
            tempTile.y = y + (MAP_WIDTH * MAP_HEIGHT * mapid);

            // get the id:type for each tile of the map
            fscanf(fileHandle, "%d:%d ", &tempTile.spriteID, &tempTile.typeID);

            //printf("id=%i sprite=%d type=%d\n", tempTile.tileID, tempTile.spriteID, tempTile.typeID);

            tileList.push_back(tempTile);
        }
        fscanf(fileHandle, "\n");
    }

    fclose(fileHandle);

    return true;
}

void TileMap::render(SDL_Surface* screen, int mapX, int mapY) {
    if(tilesetSprite == NULL) return;

    int tilesetWidth = tilesetSprite->w / TILE_SIZE;
    //int tilesetHeight = tilesetSprite->h / TILE_SIZE;

    int id = 0;


    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            if(tileList[id].typeID == Tile::TILETYPE_NONE) {
                id++;
                continue;
            }

            int tx = mapX + (x * TILE_SIZE);
            int ty = mapY + (y * TILE_SIZE);

            int tilesetX = (tileList[id].spriteID % tilesetWidth) * TILE_SIZE;
            int tilesetY = (tileList[id].spriteID / tilesetWidth) * TILE_SIZE;

            SpriteLoader::render(screen, tilesetSprite, tx, ty, tilesetX, tilesetY, TILE_SIZE, TILE_SIZE);

            if(tileList[id].selected == true) SpriteLoader::render(screen, tilesetSprite, tx, ty, 4 * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE);

            id++;
        }
    }
}

Tile* TileMap::getTileAt(int x, int y) {
    int id = 0;

    id = x / TILE_SIZE;
    id = id + (MAP_WIDTH * (y / TILE_SIZE));

    if(id < 0 || id >= tileList.size()) return NULL;

    return &tileList[id];
}

Tile* TileMap::getTileId(int id) {
    if(id < 0 || id >= tileList.size()) return NULL;
    return &tileList[id];
}

std::vector<Tile>* TileMap::getTileList() {
    return &tileList;
}
