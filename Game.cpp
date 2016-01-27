#include "Game.hpp"

Game Game::instance;

Game::Game() {
    screen = NULL;
    running = true;
    FPS = 60;
    gameFps = 0;
    lastCurTime = 0;
    lastTime = 0;
    lastTimeSF = 0;
}

int Game::startGame() {
    if(initGame() == -1) return false;

    SDL_Event event;

    int tickCount = 0;

    while(running) {
        while(SDL_PollEvent(&event)) {
            eventTriggered(&event);
        }

        //std::cout << "running: " << running << std::endl;
        int curTime = SDL_GetTicks();
        if(curTime - lastTime >= 1000 / FPS) {
            lastTime = SDL_GetTicks();
            update();
            render();
            Globals::setSpeedFactor(((SDL_GetTicks() - lastTimeSF) / 1000.0f) * FPS);
            gameFps++;
            tickCount++;
        }

        if(curTime - lastCurTime >= 1000) {
            static char buffer[100] = {0};
            sprintf(buffer, "TOWERS -- -- FPS: %i  ticks: %i Speed: %d", gameFps, tickCount, Globals::getSpeedFactor());
            SDL_WM_SetCaption(buffer, 0);
            gameFps = 0;
            tickCount = 0;
            lastCurTime = curTime;
        }
        lastTimeSF = SDL_GetTicks();
    }

    cleanup();
    return 0;
}

bool Game::initGame() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
    if(TTF_Init() < 0) return false;
    char buffer[100];
    sprintf(buffer, "%sSF Square Head.ttf", RESSOURCEDIR);
    Globals::setFont(TTF_OpenFont(buffer, 14));
    if(Globals::getFont == NULL) return false;
    if((screen = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) return false;
    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
    GameStateManager::setActiveGameState(GAMESTATE_INTRO);
    return true;
}

void Game::eventTriggered(SDL_Event* event) {
    EventHandler::onEvent(event);
    GameStateManager::onEvent(event);
}

void Game::update() {
    GameStateManager::update();
    if(Globals::isExitClicked()) onExit();
}

void Game::render() {
    GameStateManager::render(screen);
    SDL_Flip(screen);
}

void Game::cleanup() {
    GameStateManager::setActiveGameState(GAMESTATE_NONE);
    SDL_FreeSurface(screen);
    screen = NULL;
    TTF_Quit();
    SDL_Quit();
}

void Game::onExit() {
    //printf("instance: %i this %i\n", instance.running, running);
    printf("EXIT CALLED, exitClicked: %i\n", Globals::isExitClicked());
    running = false;
    //printf("instance: %i this %i\n", instance.running, running);
}

Game* Game::getInstance() {
    return &instance;
}
