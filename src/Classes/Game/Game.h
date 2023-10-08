//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
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
    Game(const Game &game) = delete;
    Game& operator=(const Game &game) = delete;

    void init(const char *title, int x, int y, int width, int height);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() const;
};
