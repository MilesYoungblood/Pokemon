//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../../Classes/Map/Map.h"
#include "../../Classes/Player/Player.h"
#include "../../Classes/Factory/PokemonFactory.h"
#include "../../Classes/Factory/MoveFactory.h"

class Game {
private:
    static void saveData();
    static void loadData();
    static void eraseData();

public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game& operator=(const Game &) = delete;

    static void handleEvents();
    static void update();
    static void render();

    explicit operator bool() const;

    static void handleOverworldEvents();
    static void handleBattleEvents();

    static void updateOverworld();
    static void updateBattle();

    static void renderOverworld();
    static void renderBattle();
};
