#include "EventHandler.hpp"

EventHandler::EventHandler() {
}

EventHandler::~EventHandler() {
    // Do Nothing
}

void EventHandler::onEvent(SDL_Event* event) {
    switch(event->type) {
        case SDL_ACTIVEEVENT: {
            switch(event->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if(event->active.gain) onMouseFocus();
                    else onMouseBlur();
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if(event->active.gain) onInputFocus();
                    else onInputBlur();
                    break;
                }
                case SDL_APPACTIVE: {
                    if(event->active.gain) onRestore();
                    else onMinimize();
                    break;
                }
            }
            break;
        }
        case SDL_KEYDOWN: {
            onKeyDown(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
            break;
        }
        case SDL_KEYUP: {
            onKeyUp(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
            break;
        }
        case SDL_MOUSEMOTION: {
            onMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel,
                         (event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0, (event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            switch(event->button.button) {
                case SDL_BUTTON_LEFT: {
                    onLButtonDown(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    onRButtonDown(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    onMButtonDown(event->button.x, event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            switch(event->button.button) {
                case SDL_BUTTON_LEFT: {
                    onLButtonUp(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    onRButtonUp(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    onMButtonUp(event->button.x, event->button.y);
                    break;
                }
            }
            break;
        }
        case SDL_QUIT: {
            onExit();
            break;
        }
        case SDL_SYSWMEVENT: {
            // Ignore
            break;
        }
        case SDL_VIDEORESIZE: {
            onResize(event->resize.w, event->resize.h);
            break;
        }
        case SDL_VIDEOEXPOSE: {
            onExpose();
            break;
        }
        default: {
            onUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
        }
    }
}

void EventHandler::onInputFocus() {
    // Pure virtual, do nothing
}
void EventHandler::onInputBlur() {
    // Pure virtual, do nothing
}
void EventHandler::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
    // Pure virtual, do nothing
}
void EventHandler::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
    // Pure virtual, do nothing
}
void EventHandler::onMouseFocus() {
    // Pure virtual, do nothing
}
void EventHandler::onMouseBlur() {
    // Pure virtual, do nothing
}
void EventHandler::onMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {
    // Pure virtual, do nothing
}
void EventHandler::onLButtonDown(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onLButtonUp(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onRButtonDown(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onRButtonUp(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onMButtonDown(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onMButtonUp(int mX, int mY) {
    // Pure virtual, do nothing
}
void EventHandler::onMinimize() {
    // Pure virtual, do nothing
}
void EventHandler::onRestore() {
    // Pure virtual, do nothing
}
void EventHandler::onResize(int w, int h) {
    // Pure virtual, do nothing
}
void EventHandler::onExpose() {
    // Pure virtual, do nothing
}
void EventHandler::onExit() {
    // Pure virtual, do nothing
}
void EventHandler::onUser(Uint8 type, int code, void* data1, void* data2) {
    // Pure virtual, do nothing
}

