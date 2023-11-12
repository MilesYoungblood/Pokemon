//
// Created by Miles on 10/2/2023.
//

#pragma once

#include <SDL_mixer.h>
#include "../../Classes/Map/Map.h"
#include "../../Namespaces/Factories/PokemonFactory.h"
#include "../../Namespaces/Factories/ItemFactory.h"
#include "../../Namespaces/Factories/MoveFactory.h"
#include "../../Singletons/KeyManager/KeyManager.h"
#include "../../Singletons/SoundPlayer/SoundPlayer.h"
#include "../../Singletons/Stopwatch/Stopwatch.h"

inline bool print = false;

inline std::vector<int> pixelsTraveled;                             // measures how many screen pixels a trainer has moved
inline std::vector<bool> lockTrainer;                               // determines whether a trainer can move spontaneously
inline std::vector<bool> keepLooping;

inline int numPages = 1;
inline int currentPage = 1;

class Game {
private:
    inline const static std::array<int, 2> FPS{ 30, 60 };
    inline static int currentFps{ FPS[1] };

    constexpr static int WINDOW_WIDTH{ TILE_SIZE * 9 };             // width of the window
    constexpr static int WINDOW_HEIGHT{ TILE_SIZE * 7 };            // height of the window
    inline const static int SCROLL_SPEED{ TILE_SIZE / 10 / (Game::currentFps / 30) };

    constexpr static int FONT_SIZE{ 20 };                           // font size for message box text

    enum State {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    inline static State currentState{ Game::State::TITLE_SCREEN };  // determines which set of functions to use

    inline static bool isRunning{ false };                          // determines whether the gameRef is running

    inline static SDL_Window *window{ nullptr };
    inline static SDL_Renderer *renderer{ nullptr };
    inline static SDL_Event event;
    inline static Mix_Music *music{ nullptr };
    inline static SDL_Texture *text{ nullptr };
    inline static SDL_Texture *logo{ nullptr };
    inline static TTF_Font *font{ nullptr };

    const std::array<void (*)(), 3ULL> HANDLE_FUNCTIONS{
            Game::handleTitleScreenEvents, Game::handleOverworldEvents, Game::handleBattleEvents
    };

    const std::array<void (*)(), 3ULL> UPDATE_FUNCTIONS{
            Game::updateTitleScreen, Game::updateOverworld, Game::updateBattle
    };

    const std::array<void (*)(), 3ULL> RENDER_FUNCTIONS{
            Game::renderTitleScreen, Game::renderOverworld, Game::renderBattle
    };

    inline static std::array<Map, 3ULL> maps{
            Map("Route 1", "Route 1", 19, 14),
            Map("Route 2", "Rival Battle", 27, 24),
            Map("Route 3", "Gym Battle", 27, 15)
    };

    inline static int currentMapIndex;
    inline static Map *currentMap{ nullptr };

    static void handleTitleScreenEvents();

    static void updateTitleScreen();

    static void renderTitleScreen();

    static void handleOverworldEvents();

    static void updateOverworld();

    static void renderOverworld();

    static void handleBattleEvents();

    static void updateBattle();

    static void renderBattle();

    static void initializeGame();

    static void updateTrainers();

    static void checkForOpponents();

    static void renderTextBox(const std::string &message);

    static void changeMap(const std::array<int, 3> &data);

    static void saveData();

    static void loadData();

    Game();

public:
    static Game &getInstance();

    ~Game();

    Game(const Game &) = delete;

    Game(const Game &&) = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(const Game &&) = delete;

    void handleEvents();

    void update();

    void render();

    [[nodiscard]] static int getFps();

    explicit operator bool() const;
};
