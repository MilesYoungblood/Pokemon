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
    void saveData();
    void loadData();
    void eraseData();

public:
    Game();
    Game(const Game &) = delete;
    Game& operator=(const Game &) = delete;

    static void handleEvents();
    static void update();
    static void render();
    static void clean();

    explicit operator bool() const;
};
