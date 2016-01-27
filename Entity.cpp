#include "Entity.hpp"

std::vector<Entity*> Entity::entityList;

Entity::Entity() {
    entitySprite = NULL;

    x = 0;
    y = 0;

    w = 0;
    h = 0;

    id = -1;

    orientation = ORIENTATION_N;

    moveLeft = false;
    moveRight = false;
    moveUp = false;
    moveDown = false;

    type = ENTITYTYPE_GENERIC;

    dead = false;
    flags = ENTITYFLAG_XY;

    speedX = 0;
    speedY = 0;
    accelX = 0;
    accelY = 0;
    if(type == ENTITYTYPE_PLAYER) {
        maxSpeedX = 10;
        maxSpeedY = 10;
    } else {
        maxSpeedX = 5;
        maxSpeedY = 5;
        accelX = 5;
        accelY = 5;
    }

    curFrameCol = 0;
    curFrameRow = 0;
    colx = 0;
    coly = 0;
    colw = 0;
    colh = 0;

    curTile = NULL;
    nextTile = NULL;
    nextReached = true;
    turnTime = 0;
}

Entity::~Entity() {
}

bool Entity::load(char* file, int w, int h, int maxFrames, int id) {
    if((entitySprite = SpriteLoader::loadPNG(file)) == NULL) return false;

    this->w = w;
    this->h = h;

    this->id = id;

    animControl.maxFrames = maxFrames;

    if(type == ENTITYTYPE_ENEMY) {
        for(int y = 0; y < MAP_HEIGHT; y++) {
            for(int x = 0; x < MAP_WIDTH; x++) {
                scanned[x][y] = -1;
                path[x][y] = -1;
            }
        }
    }

    return true;
}

bool Entity::loadBMP(char* file, int w, int h, int maxFrames, int id) {
    if((entitySprite = SpriteLoader::loadBMP(file)) == NULL) return false;

    SpriteLoader::makeTransparent(entitySprite, 0, 138, 118);

    this->w = w;
    this->h = h;

    this->id = id;

    animControl.maxFrames = maxFrames;

    if(type == ENTITYTYPE_ENEMY) {
        for(int y = 0; y < MAP_HEIGHT; y++) {
            for(int x = 0; x < MAP_WIDTH; x++) {
                scanned[x][y] = -1;
                path[x][y] = -1;
            }
        }
    }

    return true;
}

void Entity::update() {
    // Follow path
    if(type == ENTITYTYPE_ENEMY) {

    printf("%i is at %f, %f\r", id, x, y);
        if(nextTile) {
            int ntx = nextTile->x;
            int nty = nextTile->y;
            printf("next is at %i, %i\r", ntx * TILE_SIZE, nty * TILE_SIZE);
            int ntid = nextTile->tileID;
            printf("this id %i; %i, %i; curtile %i, %i; next tile %i, %i tile id %i\r",
                   id, (int) (x / TILE_SIZE), (int) (y / TILE_SIZE), curTile->x, curTile->y, ntx, nty, ntid);
            //printf("moving %i, %i to %i, %i, tile id %i\r", x/TILE_SIZE, y/TILE_SIZE, ntx, nty, ntid);
            /*if(((moveRight || moveDown) && ((int) (x / TILE_SIZE) == ntx && (int) (y / TILE_SIZE) == nty)) ||
                (moveLeft && ((int) (x / TILE_SIZE) == ntx && (int) (y / TILE_SIZE) == nty)) ||
                (moveUp && ((int) (x / TILE_SIZE) == ntx && (int) (y / TILE_SIZE) == nty))) {*/
            /*if(((int) x == ntx * TILE_SIZE && (int) y == nty * TILE_SIZE) ||
               (moveRight && (int) x - 1 == ntx * TILE_SIZE && (int) y == nty * TILE_SIZE) ||
               (moveLeft && (int) x + 1 == ntx * TILE_SIZE && (int) y == nty * TILE_SIZE) ||
               (moveDown && (int) x == ntx * TILE_SIZE && (int) y - 1 == nty * TILE_SIZE) ||
               (moveUp && (int) x == ntx * TILE_SIZE && (int) y + 1 == nty * TILE_SIZE)) {*/
            if((/*(moveRight || moveDown) &&*/ (int) x / TILE_SIZE == ntx && (int) y / TILE_SIZE == nty) /*||
               (moveLeft && (int) x / TILE_SIZE == ntx && (int) y / TILE_SIZE == nty && (int) x < ntx * TILE_SIZE)*/) {
                printf("MOVE WAS RESET AT %i,%i, nexttile %i,%i\r", (int) x / TILE_SIZE, (int) y / TILE_SIZE, ntx, nty);
                bool prevMove = -1;
                if(moveUp) prevMove = ORIENTATION_N;
                else if(moveRight) prevMove = ORIENTATION_E;
                else if(moveDown) prevMove = ORIENTATION_S;
                else if(moveLeft) prevMove = ORIENTATION_W;
                moveRight = false;
                moveLeft = false;
                moveUp = false;
                moveDown = false;
                nextTile = NULL;
                nextReached = true;
                curTile = MapArea::areaControl.getTileAt(x, y);
                if(moveRight && (int) x - 1 == ntx * TILE_SIZE) x = ntx * TILE_SIZE;
                if(moveLeft && (int) x + 1 == ntx * TILE_SIZE) x = ntx * TILE_SIZE;
                if(moveDown && (int) y - 1 == nty * TILE_SIZE) y = nty * TILE_SIZE;
                if(moveUp && (int) y + 1 == nty * TILE_SIZE) y = nty * TILE_SIZE;
                if(orientation != prevMove)
                    turnTime = 30;
            } else {
                if(turnTime > 0) {
                    printf("turntime: %i, orientation: %i\r", turnTime, orientation);
                    if(turnTime == 30) {
                        if(orientation == ORIENTATION_N) {
                            if((int) x / TILE_SIZE < ntx) orientation = ORIENTATION_NE;
                            if((int) x / TILE_SIZE > ntx) orientation = ORIENTATION_NW;
                        } else if(orientation == ORIENTATION_S) {
                            if((int) x / TILE_SIZE < ntx) orientation = ORIENTATION_SE;
                            if((int) x / TILE_SIZE > ntx) orientation = ORIENTATION_SW;
                        } else if(orientation == ORIENTATION_W) {
                            if((int) y / TILE_SIZE < nty) orientation = ORIENTATION_NW;
                            if((int) y / TILE_SIZE > nty) orientation = ORIENTATION_SW;
                        } else if(orientation == ORIENTATION_E) {
                            if((int) y / TILE_SIZE > nty) orientation = ORIENTATION_NE;
                            if((int) y / TILE_SIZE < nty) orientation = ORIENTATION_SE;
                        }
                    }
                    if(turnTime == 15) {
                        if(orientation == ORIENTATION_NE) {
                            if((int) x / TILE_SIZE < ntx) orientation = ORIENTATION_E;
                            if((int) y / TILE_SIZE < nty) orientation = ORIENTATION_N;
                        } else if(orientation = ORIENTATION_SE) {
                            if((int) x / TILE_SIZE < ntx) orientation = ORIENTATION_E;
                            if((int) y / TILE_SIZE > nty) orientation = ORIENTATION_S;
                        } else if(orientation = ORIENTATION_NW) {
                            if((int) x / TILE_SIZE > ntx) orientation = ORIENTATION_W;
                            if((int) y / TILE_SIZE < nty) orientation = ORIENTATION_N;
                        } else if(orientation = ORIENTATION_SW) {
                            if((int) x / TILE_SIZE > ntx) orientation = ORIENTATION_W;
                            if((int) y / TILE_SIZE > nty) orientation = ORIENTATION_S;

                        }
                    }
                    turnTime--;
                } else {
                    if((int) (x / TILE_SIZE) != ntx) {
                        if((int) (x / TILE_SIZE) < ntx && !moveRight && !moveLeft) moveRight = true;
                        else if((int) (x / TILE_SIZE) > ntx && !moveRight && !moveLeft) moveLeft = true;
                    } else {
                        if((int) (y / TILE_SIZE) != nty) {
                            if((int) (y / TILE_SIZE) < nty && !moveDown && !moveUp) moveDown = true;
                            else if((int) (y / TILE_SIZE) > nty && !moveDown && !moveUp) moveUp = true;
                        }
                        if(moveRight) printf("moving right from %f, %f at %f\r", x, y, speedX);
                        if(moveLeft) printf("moving left from %f, %f at %f\r", x, y, speedX);
                        if(moveUp) printf("moving up from %f, %f at %f\r", x, y, speedY);
                        if(moveDown) printf("moving down from %f, %f at %f\r", x, y, speedY);
                    }
                }
            }
        }
    }

    // Not Moving
    if(moveLeft == false && moveRight == false) stopMoveX();
    if(moveUp == false && moveDown == false) stopMoveY();

    if(moveLeft) {
        //accelX = -0.5;
        accelX = - 5;
        orientation = ORIENTATION_W;
    } else {
        if(moveRight) {
            //accelX = 0.5;
            accelX = 5;
            orientation = ORIENTATION_E;
        }
    }
    if(moveUp) {
        //accelY = -0.5;
        accelY = -5;
        orientation = ORIENTATION_N;
    } else {
        if(moveDown) {
            //accelY = 0.5;
            accelY = 5;
            orientation = ORIENTATION_S;
        }
    }

    /*if(flags & ENTITYFLAG_GRAVITY) {
        accelY = 0.75f;
    }
    if(flags & ENTITYFLAG_GHOST) {
        if(moveUp) {
            accelY = -0.5;
            orientation = ORIENTATION_N;
        } else {
            if(moveDown) {
                accelY = 0.5;
                orientation = ORIENTATION_S;
            }
        }
    }*/

    speedX += accelX * Globals::getSpeedFactor();
    speedY += accelY * Globals::getSpeedFactor();

    if(speedX > maxSpeedX) speedX = maxSpeedX;
    if(speedX < -maxSpeedX) speedX = -maxSpeedX;
    if(speedY > maxSpeedY) speedY = maxSpeedY;
    if(speedY < -maxSpeedY) speedY = -maxSpeedY;

    animate();
    onMove(speedX, speedY);
    //curTile = MapArea::areaControl.getTileAt(x, y);
}


void Entity::render(SDL_Surface* screen) {
    if(entitySprite == NULL || screen == NULL) return;

    /*SpriteLoader::render(screen, entitySprite, x - CameraHandler::cameraControl.getX(), y - CameraHandler::cameraControl.getY(),
                     curFrameCol * w, (curFrameRow + animControl.getCurFrame()) * h, w, h);*/
     SpriteLoader::render(screen, entitySprite,
                            x + (TILE_SIZE - w) / 2 - CameraHandler::cameraControl.getX(),
                            y + (TILE_SIZE - h) / 2 - CameraHandler::cameraControl.getY(),
                            orientation * w,
                            (curFrameRow + animControl.getCurFrame()) * h,
                            w, h);

    SDL_Surface* testy = NULL;
    SDL_Surface* testn = NULL;
    char buffer[100];
    sprintf(buffer, "%spathy.png", RESSOURCEDIR);
    testy = SpriteLoader::loadPNG(buffer);
    sprintf(buffer, "%spathn.png", RESSOURCEDIR);
    testn = SpriteLoader::loadPNG(buffer);
    for(int yy = 0; yy < MAP_HEIGHT; yy++) {
        for(int xx = 0; xx < MAP_WIDTH; xx++) {
            //printf("coord %i,%i is %i\r\n", xx, yy, path[xx][yy]);
            if(path[xx][yy] > 0) {
                //printf("OK! coord %i,%i is %i\r\n", xx, yy, MapArea::areaControl.getTileAt(xx, yy)->typeID);
                SpriteLoader::render(screen, testy, xx * TILE_SIZE - CameraHandler::cameraControl.getX(), yy * TILE_SIZE - CameraHandler::cameraControl.getY(),
                                      0, 0, TILE_SIZE, TILE_SIZE);
                //nextTile = MapArea::areaControl.getTileAt(xx, yy);
            }/* else {
                SpriteLoader::render(screen, testn, xx * TILE_SIZE - CameraHandler::cameraControl.getX(), yy * TILE_SIZE - CameraHandler::cameraControl.getY(),
                                      0, 0, TILE_SIZE, TILE_SIZE);
            }*/
        }
    }
}

void Entity::cleanup() {
    if(entitySprite) {
        SDL_FreeSurface(entitySprite);
    }

    entitySprite = NULL;
}

void Entity::animate() {
    if(moveLeft) {
        curFrameCol = 0;
    } else {
        if(moveRight) curFrameCol = 1;
    }

    animControl.animate();
}

bool Entity::handleCollision(Entity* entity) {
}

void Entity::onMove(float mx, float my) {
    // OnMove(1, 0) = move 1px/s
    if(mx == 0 && my == 0) return;

    double nx = 0;
    double ny = 0;

    mx *= Globals::getSpeedFactor();
    my *= Globals::getSpeedFactor();

    if(mx != 0) {
        if(mx >= 0) nx = Globals::getSpeedFactor();
        else nx = - Globals::getSpeedFactor();
    }

    if(my != 0) {
        if(my >= 0) ny = Globals::getSpeedFactor();
        else ny = - Globals::getSpeedFactor();
    }

    printf("moving to %f, %f\r", x + nx, y + ny);

    x += nx;
    y += ny;

    /*while(true) {
        if(flags & ENTITYFLAG_GHOST) {
            // Move regardless
            posValid((int) (x + nx), (int) (y + ny));
            x += nx;
            y += ny;
        } else {
            // collision checks
            if(posValid((int) (x + nx), (int) y)) {
                x += nx;
            } else {
                speedX = 0;
            }

            if(posValid((int) x, (int) (y + ny))) {
                y += ny;
            } else {
                speedY = 0;
            }
        }

        mx += -nx;
        my += -ny;

        if(nx > 0 && mx <= 0) nx = 0;
        if(nx < 0 && mx >= 0) nx = 0;

        if(ny > 0 && my <= 0) ny = 0;
        if(ny < 0 && my >= 0) ny = 0;

        if(mx == 0) nx = 0;
        if(my == 0) ny = 0;

        if(mx == 0 && my == 0) break;
        if(nx == 0 && ny == 0) break;
    }*/
}

void Entity::stopMoveX() {
    // Decrease acceleration
    /*if(speedX > 0) accelX = -1;
    if(speedX < 0) accelX = 1;
    // Limit of slowness
    if(speedX < 2.0f && speedX > -2.0f) {
        accelX = 0;
        speedX = 0;
    }*/
    accelX = 0;
    speedX = 0;
    x = (int) x;
    if(type == ENTITYTYPE_ENEMY) printf("stopped horizontal move at %f\r", x);
}

void Entity::stopMoveY() {
    /*if(speedY > 0) accelY = -1;
    if(speedY < 0) accelX = 1;
    if(speedY < 2.0f && speedY > -2.0f) {
        accelY = 0;
        speedY = 0;
    }*/
    accelY = 0;
    speedY = 0;
    y = (int) y;
    if(type == ENTITYTYPE_ENEMY) printf("stopped vertical move at %f\r", y);
}

bool Entity::collides(int ox, int oy, int ow, int oh) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

    int tx = (int) x + colx;
    int ty = (int) y + coly;

    left1 = tx;
    left2 = ox;

    right1 = left1 + w - 1 - colw;
    right2 = ox + ow - 1;

    top1 = ty;
    top2 = oy;

    bottom1 = top1 + h - 1 - colh;
    bottom2 = oy + oh - 1;

    if(bottom1 < top2) return false;
    if(top1 > bottom2) return false;

    if(right1 < left2) return false;
    if(left1 > right2) return false;

    return true;
}

bool Entity::posValid(int nx, int ny) {
    bool ret = true;

    // Get area of tiles which entity is over
    int startX = (nx + colx) / TILE_SIZE;
    int startY = (ny + coly) / TILE_SIZE;
    int endX = ((nx + colx) + w - colw - 1) / TILE_SIZE;
    int endY = ((ny + coly) + h - colh - 1) / TILE_SIZE;

    for(int iy = startY; iy <= endY; iy++) {
        for(int ix = startX; ix <= endX; ix++) {
            Tile* tile = MapArea::areaControl.getTileAt(ix * TILE_SIZE, iy * TILE_SIZE);

            // Check if valid tile to move on
            if(posValidTile(tile) == false) ret = false;
        }
    }

    if(flags & ENTITYFLAG_MAPONLY) {
    } else {
        for(int i = 0; i < entityList.size(); i++) {
            if(posValidEntity(entityList[i], nx, ny) == false) ret = false;
        }
    }
    return ret;
}

bool Entity::posValidTile(Tile* tile) {
    if(tile == NULL) return true;

    if(tile->typeID == Tile::TILETYPE_BLOCK) return false;

    return true;
}

bool Entity::posValidEntity(Entity* entity, int nx, int ny) {
    // Check if Entity is not this, not null, not dead, not maponly
    if(this != entity && entity != NULL && entity->dead == false &&
       entity->flags ^ ENTITYFLAG_MAPONLY &&
       entity->collides(nx + colx, ny + coly, w - colw - 1, h - colh - 1) == true) {

        // Entity collides = add it to collision queue
        CollisionHandler collision;

        collision.entityA = this;
        collision.entityB = entity;

        CollisionHandler::entityColQueue.push_back(collision);

        return false;
    }

    return true;
}

void Entity::setSpeedX(float speedX) {
    this->speedX = speedX;
}

void Entity::setSpeedY(float speedY) {
    this->speedY = speedY;
}
