//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "../../Classes/Map/Map.h"
#include "../../Namespaces/Factories/PokemonFactory.h"
#include "../../Namespaces/Factories/ItemFactory.h"
#include "../../Namespaces/Factories/MoveFactory.h"
#include "../../Singletons/KeyManager/KeyManager.h"
#include "../../Singletons/Stopwatch.h"

inline Direction oppositeDirection(const Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        default:
            throw std::runtime_error("Unexpected error: function oppositeDirection");
    }
}

void handleTitleScreenEvents();

void updateTitleScreen();

void renderTitleScreen();

void handleOverworldEvents();

void updateOverworld();

void renderOverworld();

void handleBattleEvents();

void updateBattle();

void renderBattle();

enum GameState {
    TITLE_SCREEN, OVERWORLD, BATTLE
};

inline const std::array<int, 2> FPS{ 30, 60 };                  // FPS is 30 during overworld, and 60 during battles
inline int currentFps = FPS[0];

inline constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;       // width of the window
inline constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;      // height of the window
inline constexpr static int SCROLL_SPEED = TILE_SIZE / 10;      // scroll speed

inline constexpr static int FONT_SIZE = 20;                     // font size for message box text

inline SDL_Window *gameWindow = nullptr;                        // global game window
inline SDL_Renderer *gameRenderer = nullptr;                    // global game renderer
inline SDL_Event event;                                         // global event object
inline Mix_Music *gameMusic = nullptr;                          // global music player
inline SDL_Texture *text = nullptr;                             // reusable text texture
inline SDL_Texture *logo = nullptr;
inline TTF_Font *textFont = nullptr;                            // global message box font

inline bool isRunning = false;                                  // determines whether the game is running

inline bool print = false;

inline Player *player = nullptr;

inline std::vector<int> walkCounters;                           // measures how many screen pixels a trainer has moved
inline std::vector<bool> lockTrainer;                           // determines whether a trainer can move spontaneously
inline std::vector<bool> keepLooping;

inline std::array<Map, 3> maps{
        Map("Route 1", "TrainerBattle.mp3", 13, 10),
        Map("Route 2", "RivalBattle.mp3", 21, 20),
        Map("Route 3", "GymBattle.mp3", 21, 11)
};

inline int currentMapIndex;
inline Map *currentMap = nullptr;

inline GameState gameState = TITLE_SCREEN;              // determines which set of functions to use

inline const int NUM_FUNCTION_STATES = 3;

inline const static std::array<void (*)(), NUM_FUNCTION_STATES> HANDLE_FUNCTIONS{
        handleTitleScreenEvents, handleOverworldEvents, handleBattleEvents
};
inline const static std::array<void (*)(), NUM_FUNCTION_STATES> UPDATE_FUNCTIONS{
        updateTitleScreen, updateOverworld, updateBattle
};
inline const static std::array<void (*)(), NUM_FUNCTION_STATES> RENDER_FUNCTIONS{
        renderTitleScreen, renderOverworld, renderBattle
};

struct Game {
    Game();

    ~Game();

    Game(const Game &) = delete;

    Game(const Game &&) = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(const Game &&) = delete;

    static void handleEvents();

    static void update();

    static void render();

    static void saveData();

    static void loadData();

    explicit operator bool() const;
};
