#include "DialogBox.hpp"

DialogBox::DialogBox() {
    sprite = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    visible = false;
}

DialogBox::DialogBox(int x, int y, int w, int h, int buttons) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->buttons = buttons;
    switch(buttons) {
        case OK:
            char fileBuffer[100] = {0};
            sprintf(fileBuffer, "%sExit.png", RESSOURCEDIR);
            DialogButton* button = new DialogButton(DialogButton::DIALOGBUTTON_YES, WWIDTH/2, WHEIGHT/2, 40, 30, fileBuffer);
            dialogButtons.push_back(button);
            break;
    }
    if(this->w < 3) this->w = 3;
    if(this->h < 3) this->h = 3;
    visible = true;
    char buffer[100];
    sprintf(buffer, "%sdialogbox.png", RESSOURCEDIR);
    sprite = SpriteLoader::loadPNG(buffer);
    listFiles();
}

void DialogBox::onMouseMove(int mx, int my, int relx, int rely, bool left, bool right, bool middle) {
    if((mx > x) && (mx < x + w * 32) && (my > y) && (my < y + h * 32)) {
        hovered = true;
    }
    for(int i = 0; i < dialogButtons.size(); i++) {
        dialogButtons[i]->onMouseMove(mx, my, relx, rely, left, right, middle);
    }
}

void DialogBox::update() {

}

void DialogBox::render(SDL_Surface* screen) {
    for(int ys = 0; ys < h; ys++) {
        for(int xs = 0; xs < w; xs++) {
            // Top
            if(xs == 0 && ys == 0) SpriteLoader::render(screen, sprite, x + xs, y + ys, 0, 0, TILE_SIZE, TILE_SIZE);
            else if(xs > 0 && xs < w - 1 && ys == 0) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 32, 0, TILE_SIZE, TILE_SIZE);
            else if(xs == w - 1 && ys == 0) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 2 * 32, 0, TILE_SIZE, TILE_SIZE);
            // Mid
            else if(xs == 0 && ys > 0 && ys < h - 1) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 0, 32, TILE_SIZE, TILE_SIZE);
            else if(xs == w - 1 && ys > 0 && ys < h - 1) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 32 * 2, 32, TILE_SIZE, TILE_SIZE);
            // Bottom
            else if(xs == 0 && ys == h - 1) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 0, 2 * 32, TILE_SIZE, TILE_SIZE);
            else if(xs > 0 && xs < w - 1 && ys == h - 1) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 32, 2 * 32, TILE_SIZE, TILE_SIZE);
            else if(xs == w - 1 && ys == h - 1) SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 2 * 32, 2 * 32, TILE_SIZE, TILE_SIZE);
            else SpriteLoader::render(screen, sprite, x + xs * 32, y + ys * 32, 32, 32, TILE_SIZE, TILE_SIZE);
        }
    }
    for(int i = 0; i < dialogButtons.size(); i++) {
        dialogButtons[i]->render(screen);
    }
}

void DialogBox::cleanup() {
    if(sprite) SDL_FreeSurface(sprite);
    sprite = NULL;
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    visible = false;
    for(int i = 0; i < dialogButtons.size(); i++) {
        delete dialogButtons[i];
    }
}

void DialogBox::listFiles() {
    DIR *pDir;
    struct dirent *entry;
    if(pDir = opendir("./maps/user")) {
        while(entry = readdir(pDir)) {
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                mapsInFolder.push_back(entry->d_name);
        }
        closedir(pDir);
    }
}
