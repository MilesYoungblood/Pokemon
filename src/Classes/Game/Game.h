//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../../Classes/Map/Map.h"
#include "../../Namespaces/Factory/PokemonFactory.h"
#include "../../Namespaces/Factory/ItemFactory.h"
#include "../../Namespaces/Factory/MoveFactory.h"

inline Direction oppositeDirection(const Direction direction) {
    switch (direction) {
        case NORTH:
            return Direction::SOUTH;
        case EAST:
            return Direction::WEST;
        case SOUTH:
            return Direction::NORTH;
        case WEST:
            return Direction::EAST;
        default:
            throw std::runtime_error("Unexpected error: function oppositeDirection");
    }
}

class Game {
private:
    static void saveData();
    static void loadData();
    static void eraseData();

    static void handleOverworldKeyDown();

    static void changeMap(const std::array<int, 3> &data);
    static void checkForOpponents();
    static void updateTrainers();

public:
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game(const Game &&) = delete;
    Game & operator=(const Game &) = delete;
    Game & operator=(const Game &&) = delete;

    static void handleEvents();
    static void update();
    static void render();

    static void handleTitleScreenEvents();
    static void handleOverworldEvents();
    static void handleBattleEvents();

    static void updateTitleScreen();
    static void updateOverworld();
    static void updateBattle();

    static void renderTitleScreen();
    static void renderOverworld();
    static void renderBattle();

    explicit operator bool() const;
};
