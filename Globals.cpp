#include "Globals.hpp"

bool Globals::exitClicked = 0;
float Globals::speedFactor = 0.0f;
TTF_Font* Globals::font = NULL;

bool Globals::isExitClicked() {
    return exitClicked;
}

float Globals::getSpeedFactor() {
    return speedFactor;
}

TTF_Font* Globals::getFont() {
    return font;
}

void Globals::setExitClicked(bool clicked) {
    exitClicked = clicked;
}

void Globals::setSpeedFactor(float sf) {
    speedFactor = sf;
}

void Globals::setFont(TTF_Font* afont) {
    font = afont;
}
