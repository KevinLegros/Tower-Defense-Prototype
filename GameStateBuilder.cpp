#include "GameStateBuilder.hpp"

GameStateBuilder GameStateBuilder::instance;

GameStateBuilder::GameStateBuilder() {
    cameraMoving = false;
    BuilderUI = NULL;
    currentTile = -1;
    oldTile = -1;
    message = NULL;
    dialogBox = NULL;
}

void GameStateBuilder::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
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

void GameStateBuilder::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
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
        default: {
        }
    }
}

void GameStateBuilder::onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle) {
    if(dialogBox) if(dialogBox->visible == true) return;

    for(int i = 0; i < tileButtons.size(); i++) {
        tileButtons[i]->onMouseMove(mx, my, relx, rely, left, right, middle);
    }
    if(left) {
        player.x -= relx;
        player.y -= rely;
        cameraMoving = true;
    }

    for(int i = 0; i < builderButtons.size(); i++) {
        builderButtons[i]->onMouseMove(mx, my, relx, rely, left, right, middle);
    }

    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;

    if(MapArea::areaControl.tileHover > -1) {
        Tile* hoveredTile = MapArea::areaControl.getTileId(MapArea::areaControl.tileHover);
        if(hoveredTile->tileID != MapArea::areaControl.getTileAt(cx, cy)->tileID) {
            if(oldTile > -1) {
                hoveredTile->spriteID = oldTile;
                oldTile = -1;
            } else {
                hoveredTile->spriteID = hoveredTile->spriteID - 15;
            }
            MapArea::areaControl.tileHover = -1;
        }
    }

    if(mx > WWIDTH - 150) return;
    Tile* tile = MapArea::areaControl.getTileAt(cx, cy);
    if(tile->tileID != MapArea::areaControl.tileHover) {
        if(currentTile > -1) {
            oldTile = tile->spriteID;
            tile->spriteID = currentTile;
        } else {
            tile->spriteID = tile->spriteID + 15;
        }
        tile->hovered = true;
        MapArea::areaControl.tileHover = tile->tileID;
    }

}

void GameStateBuilder::onLButtonDown(int mx, int my) {
    if(dialogBox) if(dialogBox->visible == true) return;

    for(int i = 0; i < tileButtons.size(); i++) {
        tileButtons[i]->onLButtonDown(mx, my);
    }
    for(int i = 0; i < builderButtons.size(); i++) {
        builderButtons[i]->onLButtonDown(mx, my);
    }
    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;
}

void GameStateBuilder::onLButtonUp(int mx, int my) {
    if(dialogBox) if(dialogBox->visible == true) return;

    if(mx > WWIDTH - 150 && my < 30 + 42 + 42 + 42 + 42 + 32) {
        for(int i = 0; i < tileButtons.size(); i++) {
            tileButtons[i]->selected = false;
            tileButtons[i]->onLButtonUp(mx, my);
            if(tileButtons[i]->selected == true) currentTile = tileButtons[i]->id - 100;
        }
    }
    for(int i = 0; i < builderButtons.size(); i++) {
        if(!builderButtons[i]) continue;
        builderButtons[i]->onLButtonUp(mx, my);
        if(builderButtons.size() == 0) break;
        if(builderButtons[i]->id == BuilderButton::BUILDERBUTTON_EXIT) break;
        printf("%i\r\n", builderButtons[i]->id);
        if(builderButtons[i]->isClicked()) {
            if(builderButtons[i]->id == BuilderButton::BUILDERBUTTON_LOAD) {
                //dialogBox.init(32 * 7, 32 * 4, 8, 8, DialogBox::OK_CANCEL);
                dialogBox = new DialogBox(32 * 7, 32 * 4, 8, 8, DialogBox::OK_CANCEL);
                SDL_Color textColor = {255, 255, 255};
                message = TTF_RenderText_Solid(Globals::getFont(), "Load a map", textColor);
                for(int i = 0; i < dialogBox->mapsInFolder.size(); i++) {
                    mapsNames.push_back(TTF_RenderText_Solid(Globals::getFont(), dialogBox->mapsInFolder[i].c_str(), textColor));
                }
            } else if(builderButtons[i]->id == BuilderButton::BUILDERBUTTON_SAVE) {

            }
        }
    }


    if(cameraMoving) {
        cameraMoving = false;
        return;
    }
    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;
    if(mx < WWIDTH - 150) {
        Tile* hoveredTile = MapArea::areaControl.getTileAt(cx, cy);
        if(currentTile > -1) {
            oldTile = currentTile;
            hoveredTile->spriteID = currentTile;
        }
    }
}

void GameStateBuilder::onRButtonUp(int mx, int my) {
    int cx = CameraHandler::cameraControl.getX() + mx;
    int cy = CameraHandler::cameraControl.getY() + my;
    /*for(int i = 0; i < tileButtons.size(); i++) {
        tileButtons[i]->selected = false;
    }
    currentTile = -1;
    oldTile = -1;*/
}


void GameStateBuilder::onActivate() {
    char fileBuffer[100] = {0};

    sprintf(fileBuffer, "%sgrasstiles.png", RESSOURCEDIR);

    tileButtons.push_back(new BuilderButton(TILEBUTTON_NW, WWIDTH - 130, 30, 32, 32, 0, 0, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_N, WWIDTH - 130 + 42, 30, 32, 32, 32, 0, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_NE, WWIDTH - 130 + 42 + 42, 30, 32, 32, 64, 0, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_W, WWIDTH - 130, 30 + 42, 32, 32, 0, 32, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_C, WWIDTH - 130 + 42, 30 + 42, 32, 32, 32, 32, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_E, WWIDTH - 130 + 42 + 42, 30 + 42, 32, 32, 64, 32, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_SW, WWIDTH - 130, 30 + 42 + 42, 32, 32, 0, 64, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_S, WWIDTH - 130 + 42, 30 + 42 + 42, 32, 32, 32, 64, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_SE, WWIDTH - 130 + 42 + 42, 30 + 42 + 42, 32, 32, 64, 64, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_BNW, WWIDTH - 130, 30 + 42 + 42 + 42, 32, 32, 96, 0, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_BNE, WWIDTH - 130 + 42, 30 + 42 + 42 + 42, 32, 32, 128, 0, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_BSW, WWIDTH - 130, 30 + 42 + 42 + 42 + 42, 32, 32, 96, 32, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_BSE, WWIDTH - 130 + 42, 30 + 42 + 42 + 42 + 42, 32, 32, 128, 32, fileBuffer));
    tileButtons.push_back(new BuilderButton(TILEBUTTON_CC, WWIDTH - 130 + 42 + 42, 30 + 42 + 42 + 42, 32, 32, 96, 64, fileBuffer));

    sprintf(fileBuffer, "%sLoad.png", RESSOURCEDIR);
    builderButtons.push_back(new BuilderButton(BuilderButton::BUILDERBUTTON_LOAD, WWIDTH - 100, WHEIGHT - 100, 40, 30, 0, 0, fileBuffer));
    sprintf(fileBuffer, "%sSave.png", RESSOURCEDIR);
    builderButtons.push_back(new BuilderButton(BuilderButton::BUILDERBUTTON_SAVE, WWIDTH - 50, WHEIGHT - 100, 40, 30, 0, 0, fileBuffer));
    sprintf(fileBuffer, "%sExit.png", RESSOURCEDIR);
    builderButtons.push_back(new BuilderButton(BuilderButton::BUILDERBUTTON_EXIT, WWIDTH - 50, WHEIGHT - 60, 40, 30, 0, 0, fileBuffer));

    sprintf(fileBuffer, "%sBuilderUi.png", RESSOURCEDIR);
    BuilderUI = SpriteLoader::loadPNG(fileBuffer);


    if(MapArea::areaControl.load("./maps/temp.area") == false) return;

    Entity::entityList.push_back(&player);

    player.x = 400;
    player.y = 300;
    player.maxSpeedX = 50;
    player.maxSpeedY = player.maxSpeedX;
    player.flags = ENTITYFLAG_GHOST;
    CameraHandler::cameraControl.targetMode = TARGETMODE_CENTER;
    CameraHandler::cameraControl.setTarget(&player.x, &player.y);
}

void GameStateBuilder::onDeactivate() {
    for(int i = 0; i < tileButtons.size(); i++) {
        tileButtons[i]->cleanup();
        delete tileButtons[i];
        tileButtons[i] = NULL;
    }
    tileButtons.clear();
    for(int i = 0; i < builderButtons.size(); i++) {
        builderButtons[i]->cleanup();
        delete builderButtons[i];
        builderButtons[i] = NULL;
    }
    builderButtons.clear();
    if(dialogBox) dialogBox->cleanup();
    if(message) SDL_FreeSurface(message);
    message = NULL;
    for(int i = 0; i < mapsNames.size(); i++) {
        SDL_FreeSurface(mapsNames[i]);
        mapsNames[i] = NULL;
    }
    mapsNames.clear();
    MapArea::areaControl.cleanup();

    for(int i = 0; i < Entity::entityList.size(); i++) {
        if(!Entity::entityList[i]) continue;
        Entity::entityList[i]->cleanup();
    }
    Entity::entityList.clear();

    if(BuilderUI) {
        SDL_FreeSurface(BuilderUI);
        BuilderUI = NULL;
    }
    cameraMoving = false;
    BuilderUI = NULL;
    currentTile = -1;
    oldTile = -1;
}

void GameStateBuilder::update() {
    for(int i = 0; i < Entity::entityList.size(); i++) {
        if(!Entity::entityList[i]) continue;
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
}

void GameStateBuilder::render(SDL_Surface* screen) {
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
    }

    SpriteLoader::render(screen, BuilderUI, WWIDTH - 150, 0);
    for(int i = 0; i < tileButtons.size(); i++) {
        tileButtons[i]->render(screen);
    }
    for(int i = 0; i < builderButtons.size(); i++) {
        builderButtons[i]->render(screen);
    }

    if(message != NULL) {
        if(dialogBox) dialogBox->render(screen);
        SpriteLoader::render(screen, message, 32 * 8, 32 * 4 + 16);
        for(int i = 0; i < mapsNames.size(); i++) {
            SpriteLoader::render(screen, mapsNames[i], 32 * 8, 32 * 4 + 16 + 32 * (i+1));
        }
    }
}

void GameStateBuilder::loadLevel(char* area) {

}

void GameStateBuilder::saveLevel() {

}

GameStateBuilder* GameStateBuilder::getInstance() {
    return &instance;
}

