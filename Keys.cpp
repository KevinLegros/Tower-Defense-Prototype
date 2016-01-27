#include "Keys.hpp"

bool Keys::eventClicked = 0;

bool Keys::isEventClicked() {
    return eventClicked;
}

void Keys::setEventClicked(bool clicked) {
    eventClicked = clicked;
}
