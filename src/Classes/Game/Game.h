//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../../Classes/Map/Map.h"
#include "../../Namespaces/Factories/PokemonFactory.h"
#include "../../Namespaces/Factories/ItemFactory.h"
#include "../../Namespaces/Factories/MoveFactory.h"

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

inline constexpr static int FPS = 30;
inline constexpr static int FRAME_DELAY = 1000 / FPS;

inline constexpr static int WINDOW_HEIGHT = TILE_SIZE * 7;      // height of the window
inline constexpr static int WINDOW_WIDTH = TILE_SIZE * 9;       // width of the window
inline constexpr static int SCROLL_SPEED = TILE_SIZE / 10;      // scroll speed

inline constexpr static int FONT_SIZE = 20;                     // font size for message box text

inline constexpr static int NUM_FUNCTION_STATES = 3;            // number of function states

inline SDL_Window *gameWindow = nullptr;                        // global game window
inline SDL_Renderer *gameRenderer = nullptr;                    // global game renderer
inline SDL_Event event;                                         // global event object
inline Mix_Music *gameMusic = nullptr;                          // global music player
inline SDL_Texture *text = nullptr;                             // reusable text texture
inline SDL_Texture *logo = nullptr;
inline TTF_Font *textFont = nullptr;                            // global message box font

inline bool isRunning = false;                                  // determines whether the game is running

inline bool canMove = true;                                     // determines whether the player can move

inline bool canInteract = true;                                 // determines whether the player can pressedEnter

inline std::array<bool, 4> moveDirection = {                    // flags that determine when the player attempts to move
        false, false, false, false
};

inline std::array<bool, 4> keepMovingDirection = {              // ultimately, determine when the player stops moving
        false, false, false, false
};

inline bool pressedEnter = false;                               // signals when the player is trying
                                                                // to interact with something

inline bool print = false;

inline int walkCounter = 0;                                     // measures how many screen pixels the player has moved

inline std::vector<int> walkCounters;                           // measures how many screen pixels a trainer has moved
inline std::vector<bool> lockTrainer;                           // determines whether a trainer can move spontaneously

inline Player *player = nullptr;

inline std::array<std::unique_ptr<Map>, 3> maps;

inline int currentMapIndex;
inline std::unique_ptr<Map> currentMap = nullptr;

// TODO eventually change to 0 to start at title screen
inline int functionState = 0;                              // determines which set of functions to use

inline const std::array<void (*)(), NUM_FUNCTION_STATES> handleFunctions = {
        handleTitleScreenEvents, handleOverworldEvents, handleBattleEvents
};
inline const std::array<void (*)(), NUM_FUNCTION_STATES> updateFunctions = {
        updateTitleScreen, updateOverworld, updateBattle
};
inline const std::array<void (*)(), NUM_FUNCTION_STATES> renderFunctions = {
        renderTitleScreen, renderOverworld, renderBattle
};

struct Game {
    Game();
    ~Game();
    Game(const Game &) = delete;
    Game(const Game &&) = delete;
    Game & operator=(const Game &) = delete;
    Game & operator=(const Game &&) = delete;

    static void handleEvents();
    static void update();
    static void render();

    static void saveData();
    static void loadData();

    explicit operator bool() const;
};
