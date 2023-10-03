//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Classes/Map/Map.h"
#include "../../Classes/Player/Player.h"

class Game {
private:
    static Game* instancePtr;

    static Player* player;

    static Map* maps[3];
    static Map* currentMap;

    Game();

    static void run();
    static void saveData();
    static void loadData();
    static void eraseData();

public:
    Game(const Game &game) = delete;
    Game& operator=(const Game &game) = delete;

    static Game* createGame();
    static void destroyGame();
};
