//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include "../../Classes/Map/Map.h"
#include "../../Classes/Player/Player.h"

class Game {
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Player *player;

    Map *maps[3];
    Map *currentMap;
    int currentMapIndex;

    void saveData();
    void loadData();
    void eraseData();

public:
    Game();
    Game(const Game &) = delete;
    Game& operator=(const Game &) = delete;

    void handleEvents();
    void update();
    void render();
    void clean();

    explicit operator bool() const;
};
