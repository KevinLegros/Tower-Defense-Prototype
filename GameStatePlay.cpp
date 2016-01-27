#include "GameStatePlay.hpp"
#include "Game.hpp"

GameStatePlay GameStatePlay::instance;

GameStatePlay::GameStatePlay() {
    cameraMoving = false;
}

void GameStatePlay::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            player.moveLeft = true;
            player.setSpeedX(-player.maxSpeedX);
            break;
        }
        case SDLK_RIGHT: {
            player.moveRight = true;
            player.setSpeedX(player.maxSpeedX);
            break;
        }
        case SDLK_UP:
            player.moveUp = true;
            player.setSpeedY(-player.maxSpeedY);
            break;
        case SDLK_DOWN:
            player.moveDown = true;
            player.setSpeedY(player.maxSpeedY);
            break;
        case SDLK_SPACE: {
            //Player.Jump();
            break;
        }
        default: {
        }
    }
}

void GameStatePlay::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_LEFT: {
            player.moveLeft = false;
            player.setSpeedX(0);
            break;
        }
        case SDLK_RIGHT: {
            player.moveRight = false;
            player.setSpeedX(0);
            break;
        }
        case SDLK_UP:
            player.moveUp = false;
            player.setSpeedY(0);
            break;
        case SDLK_DOWN:
            player.moveDown = false;
            player.setSpeedY(0);
            break;
        case SDLK_SPACE: {
            //Player.Jump();
            break;
        }
        case SDLK_F4: {
            if(debugMessages.size() > 0) {
                for(int i = 0; i < debugMessages.size(); i++) {
                    delete debugMessages[i];
                    debugMessages[i] = NULL;
                }
                debugMessages.clear();
            } else {
                SDL_Color textColor = {255, 255, 255};
                char buffer[100];
                sprintf(buffer, "Camera: %i, %i", CameraHandler::cameraControl.getX() + WWIDTH/2, CameraHandler::cameraControl.getY() + WHEIGHT/2);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
                sprintf(buffer, "Tile: %i, %i", 0, 0);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
                sprintf(buffer, "TileId: %i", 0);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
                sprintf(buffer, "TileType: %i", 0);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
                sprintf(buffer, "Entities: %i", Entity::entityList.size());
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            if(Entity::entityList[1]->nextTile) {
                sprintf(buffer, "Entity on: %i", Entity::entityList[1]->nextTile->tileID);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            }
            }
            break;
        }
        case SDLK_ESCAPE: {
            GameStateManager::setActiveGameState(GAMESTATE_MAINMENU);
        }
        default: {
        }
    }
}

void GameStatePlay::onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle) {
    if(left) {
        player.x -= relx;
        player.y -= rely;
        cameraMoving = true;
    }

    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;
    mouseposX = cx;
    mouseposY = cy;

    if(MapArea::areaControl.tileHover > -1) {
        Tile* hoveredTile = MapArea::areaControl.getTileId(MapArea::areaControl.tileHover);
        if(hoveredTile->tileID != MapArea::areaControl.getTileAt(cx, cy)->tileID) {
            hoveredTile->spriteID = hoveredTile->spriteID - 15;
            MapArea::areaControl.tileHover = -1;
        }
    }

    Tile* tile = MapArea::areaControl.getTileAt(cx, cy);
    if(tile->tileID != MapArea::areaControl.tileHover) {
        tile->spriteID = tile->spriteID + 15;
        tile->hovered = true;
        MapArea::areaControl.tileHover = tile->tileID;
        /*if(debugMessages.size() > 0) {
            for(int i = 0; i < debugMessages.size(); i++) {
                delete debugMessages[i];
                debugMessages[i] = NULL;
            }
            debugMessages.clear();

            SDL_Color textColor = {255, 255, 255};
            char buffer[100];
            sprintf(buffer, "Camera: %i, %i", CameraHandler::cameraControl.getX() + WWIDTH/2, CameraHandler::cameraControl.getY() + WHEIGHT/2);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "Tile: %i, %i", cx / TILE_SIZE, cy / TILE_SIZE);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "TileId: %i", tile->tileID);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "TileType: %i", tile->typeID);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "Entities: %i", Entity::entityList.size());
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            if(Entity::entityList[1]->nextTile) {
                sprintf(buffer, "Entity on: %i", Entity::entityList[1]->nextTile->tileID);
                debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            }
        }*/
    }
}

void GameStatePlay::onLButtonUp(int mx, int my) {
    if(cameraMoving) {
        cameraMoving = false;
        return;
    }
    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;

    Tile* selectedTile = MapArea::areaControl.getTileAt(cx, cy);
    if(selectedTile->selected) {

    } else {
        if(MapArea::areaControl.tileSelected > -1) {
            Tile* selectedTile = MapArea::areaControl.getTileId(MapArea::areaControl.tileSelected);
            selectedTile->selected = false;
            MapArea::areaControl.tileSelected = -1;
        }
        selectedTile->selected = true;
        MapArea::areaControl.tileSelected = selectedTile->tileID;
    }
}

void GameStatePlay::onRButtonUp(int mx, int my) {
    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;

    if(MapArea::areaControl.tileSelected > -1) {
        Tile* selectedTile = MapArea::areaControl.getTileId(MapArea::areaControl.tileSelected);

        printf("deselecting tile %i", selectedTile->tileID);
        selectedTile->selected = false;
        MapArea::areaControl.tileSelected = -1;
    }
}


void GameStatePlay::onActivate() {
    if(MapArea::areaControl.load("./maps/1.area") == false) return;

    char buffer[100];
    sprintf(buffer, "%sbeast_1.png", RESSOURCEDIR);
    enemy.type = Entity::ENTITYTYPE_ENEMY;
    if(enemy.load(buffer, 20, 20, 0, 0) == false) return;
    enemy2.type = Entity::ENTITYTYPE_ENEMY;
    if(enemy2.load(buffer, 20, 20, 0, 1) == false) return;
    delete buffer;

    Entity::entityList.push_back(&player);
    Entity::entityList.push_back(&enemy);
    //Entity::entityList.push_back(&enemy2);

    //enemy.x = -20;
    //enemy.y = 32 * 5;
    enemy.x = 1 * TILE_SIZE;
    enemy.y = 10 * TILE_SIZE;
    enemy.orientation = ORIENTATION_E;
    enemy.curTile = MapArea::areaControl.getTileAt(enemy.x, enemy.y);

    enemy2.x = 15 * TILE_SIZE;
    enemy2.y = 14 * TILE_SIZE;
    enemy2.orientation = ORIENTATION_S;
    enemy2.curTile = MapArea::areaControl.getTileAt(enemy2.x, enemy2.y);

    player.x = 400;
    player.y = 300;
    player.maxSpeedX = 50;
    player.maxSpeedY = player.maxSpeedX;
    player.type = Entity::ENTITYTYPE_PLAYER;
    player.flags = ENTITYFLAG_GHOST;
    CameraHandler::cameraControl.targetMode = TARGETMODE_CENTER;
    CameraHandler::cameraControl.setTarget(&player.x, &player.y);
}

void GameStatePlay::onDeactivate() {
    MapArea::areaControl.cleanup();

    for(int i = 0; i < Entity::entityList.size(); i++) {
        if(!Entity::entityList[i]) continue;
        Entity::entityList[i]->cleanup();
    }
    Entity::entityList.clear();
    for(int i = 0; i < debugMessages.size(); i++) {
        delete debugMessages[i];
        debugMessages[i] = NULL;
    }
    player = Player();
    enemy = Enemy();
    enemy2 = Enemy();
    debugMessages.clear();
}

void GameStatePlay::update() {
    //enemy.moveRight = true;
    //enemy.setSpeedX(10);
    for(int i = 0; i < Entity::entityList.size(); i++) {
        if(!Entity::entityList[i]) continue;
        if(Entity::entityList[i]->type == Entity::ENTITYTYPE_ENEMY &&
            (!Entity::entityList[i]->nextTile &&
            Entity::entityList[i]->curTile) &&
            Entity::entityList[i]->nextReached == true) {
        //if(Entity::entityList[i]->type == Entity::ENTITYTYPE_ENEMY && Entity::entityList[i]->nextReached == true) {
    printf("\rPATHFINDING FOR %f, %f with id %i type %i place %i\r",
           Entity::entityList[i]->x,
           Entity::entityList[i]->y,
           Entity::entityList[i]->id,
           Entity::entityList[i]->type,
           i);
            pathfinding(Entity::entityList[i]);
            }
            //printf("pathfinding1 %i type %i\r", Entity::entityList[i]->getId(), Entity::entityList[i]->type);
        /*else if(Entity::entityList[i]->type == Entity::ENTITYTYPE_ENEMY && Entity::entityList[i]->nextTile && Entity::entityList[i]->curTile)
            if(Entity::entityList[i]->nextTile->tileID < 0 && Entity::entityList[i]->curTile->tileID != Entity::entityList[i]->nextTile->tileID)
                pathfinding(Entity::entityList[i]);
                //printf("pathfinding2 %i type %i\r", Entity::entityList[i]->getId(), Entity::entityList[i]->type);*/
        Entity::entityList[i]->update();
    }

    // Collisions
    for(int i = 0; i < CollisionHandler::entityColQueue.size(); i++) {
        Entity* entityA = CollisionHandler::entityColQueue[i].entityA;
        Entity* entityB = CollisionHandler::entityColQueue[i].entityB;

        if(entityA == NULL || entityB == NULL) continue;

        if(entityA->handleCollision(entityB)) {
            entityB->handleCollision(entityA);
        }
    }

    CollisionHandler::entityColQueue.clear();

    if(debugMessages.size() > 0) {
        for(int i = 0; i < debugMessages.size(); i++) {
            delete debugMessages[i];
            debugMessages[i] = NULL;
        }
        debugMessages.clear();

        SDL_Color textColor = {255, 255, 255};
        char buffer[100];
        sprintf(buffer, "Camera: %i, %i", CameraHandler::cameraControl.getX() + WWIDTH/2, CameraHandler::cameraControl.getY() + WHEIGHT/2);
        debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        sprintf(buffer, "Tile: %i, %i", mouseposX / TILE_SIZE, mouseposY / TILE_SIZE);
        debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        sprintf(buffer, "TileId: %i", MapArea::areaControl.getTileHoveredId());
        debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        sprintf(buffer, "TileType: %i", MapArea::areaControl.getTileId(MapArea::areaControl.getTileHoveredId())->typeID);
        debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        sprintf(buffer, "Entities: %i", Entity::entityList.size());
        debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        if(Entity::entityList[1]->nextTile) {
            sprintf(buffer, "Entity on: %i",
                    MapArea::areaControl.getTileAt(Entity::entityList[1]->x, Entity::entityList[1]->y)->tileID);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "Entity nextTile: %i",
                    Entity::entityList[1]->nextTile->tileID);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
            sprintf(buffer, "Entity turntime: %i", Entity::entityList[1]->turnTime);
            debugMessages.push_back(TTF_RenderText_Solid(Globals::getFont(), buffer, textColor));
        }
    }
}

void GameStatePlay::render(SDL_Surface* screen) {
    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = WWIDTH;
    Rect.h = WHEIGHT;

    SDL_FillRect(screen, &Rect, 0);

    MapArea::areaControl.render(screen, -CameraHandler::cameraControl.getX(), -CameraHandler::cameraControl.getY());

    for(int i = 0; i < Entity::entityList.size(); i++) {
        if(!Entity::entityList[i]) continue;

        Entity::entityList[i]->render(screen);

        if(debugMessages.size() > 0) {
            for(int y = 0; y < MAP_HEIGHT; y++) {
                for(int x = 0; x < MAP_WIDTH; x++) {
                        if(Entity::entityList[i]->path[x][y] > 0) {
                            SDL_Color textColor = {255, 255, 255};
                            char buffer[100];
                            sprintf(buffer, "%i", Entity::entityList[i]->path[x][y]);
                            SpriteLoader::render(screen, TTF_RenderText_Solid(Globals::getFont(), buffer, textColor),
                                                 (x * TILE_SIZE) - CameraHandler::cameraControl.getX(),
                                                 (y * TILE_SIZE) - CameraHandler::cameraControl.getY());
                        }

                }
            }
        }
    }

    if(debugMessages.size() > 0) {
        int offset = 0;
        for(int i = 0; i < debugMessages.size(); i++) {
            SpriteLoader::render(screen, debugMessages[i], 32, 32 + offset);
            offset += debugMessages[i]->h;
        }
    }
}

void GameStatePlay::pathfinding(Entity* e) {
    //Enemy* e = (Enemy*) ent;
    //printf("\rPATHFINDING FOR %i, %i with id %i type %i\r", e->x, e->y, e->id, e->type);
    int index = 0;

    /*int startx = 0;
    int starty = 5;*/
    int startx = e->x / TILE_SIZE;
    int starty = e->y / TILE_SIZE;
    int endx = 5;
    int endy = 20;
    e->scanned[endx][endy] = 0;
    if(startx == endx && starty == endy) return;

    bool done = false;
    while(!done) {
        index++;
        if(index > MapArea::areaControl.areaSize) done = true;
        for(int y = 0; y < MAP_HEIGHT; y++) {
            for(int x = 0; x < MAP_WIDTH; x++) {
                if(e->scanned[x][y] >= 0) {
                    for(int y1 = y - 1; y1 <= y + 1; y1++) {
                        for(int x1 = x - 1; x1 <= x + 1; x1++) {
                            if(y1 < MAP_HEIGHT && y1 > -1 && x1 < MAP_WIDTH && x1 > -1) {
                                if(((x1 < x || x1 > x) && y1 == y) || (x1 == x && (y1 < y || y1 > y))) {
                                    if(x1 == startx && y1 == starty) done = true;
                                    if(MapArea::areaControl.getTileAt(x1 * TILE_SIZE, y1 * TILE_SIZE)->typeID == Tile::TILETYPE_NORMAL)
                                        if(e->scanned[x1][y1] == -1) e->scanned[x1][y1] = e->scanned[x][y] + 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    done = false;
    int x1 = startx;
    int y1 = starty;
    int x;
    int y;
    int v;
    int v1;
    while(!done) {
        x = -1;
        y = -1;
        v1 = MAP_WIDTH * MAP_HEIGHT + 1;
        if(y1 - 1 >= 0) {
            v = e->scanned[x1][y1 - 1];
            if(v >= 0) {
                x = x1;
                y = y1 - 1;
                v1 = v;
            }
        }
        if(x1 - 1 >= 0) {
            v = e->scanned[x1 - 1][y1];
            if(v >= 0 && v < v1) {
                x = x1 - 1;
                y = y1;
                v1 = v;
            }
        }
        if(x1 + 1 <= MAP_WIDTH) {
            v = e->scanned[x1 + 1][y1];
            if(v >= 0 && v < v1) {
                x = x1 + 1;
                y = y1;
                v1 = v;
            }
        }
        if(y1 + 1 <= MAP_HEIGHT) {
            v = e->scanned[x1][y1 + 1];
            if(v >= 0 && v < v1) {
                x = x1;
                y = y1 + 1;
                v1 = v;
            }
        }
        if(x > -1 && y > -1) {
            if(v1 > 0 && v1 < MAP_WIDTH * MAP_HEIGHT + 1) {
                e->path[x][y] = v1;
                x1 = x;
                y1 = y;
                if(!e->nextTile) {
                    Tile* tile = MapArea::areaControl.getTileAt(x * TILE_SIZE, y * TILE_SIZE);
                    if(tile) e->nextTile = tile;
                    printf("%i next tile set to %i\r", e->id, e->nextTile->tileID);
                    e->nextReached = false;
                }
            }
            if(v1 == 0) {
                e->path[x][y] = 0;
                done = true;
            }
        } else done = true;
    }
}

GameStatePlay* GameStatePlay::getInstance() {
    return &instance;
}

