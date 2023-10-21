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
#include "../../Namespaces/Factory/PokemonFactory.h"
#include "../../Namespaces/Factory/ItemFactory.h"
#include "../../Namespaces/Factory/MoveFactory.h"

class Game {
private:
    static void saveData();
    static void loadData();
    static void eraseData();

    static void handleOverworldKeyDown();

public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    auto operator=(const Game &) -> Game& = delete;

    static void handleEvents();
    static void update();
    static void render();

    static void handleOverworldEvents();
    static void handleBattleEvents();

    static void updateOverworld();
    static void updateBattle();

    static void renderOverworld();
    static void renderBattle();

    explicit operator bool() const;
};
