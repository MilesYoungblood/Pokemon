//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Map/Map.h"
#include "../../Data/Items/Items.h"
#include "../../Data/Moves/MoveList.h"
#include "../KeyManager/KeyManager.h"
#include "../SoundPlayer/SoundPlayer.h"
#include "../Stopwatch/Stopwatch.h"

inline bool print = false;

inline std::vector<int> pixelsTraveled;                                 // measures how many screen pixels a trainer has moved
inline std::vector<bool> lockTrainer;                                   // determines whether a trainer can move spontaneously
inline std::vector<bool> keepLooping;

inline int numPages = 1;
inline int currentPage = 1;

class Game {
private:
    const std::array<int, 2> FPS{ 30, 60 };
    int currentFps{ FPS[1] };

    const int WINDOW_WIDTH{ Constants::TILE_SIZE * 9 };                            // width of the window
    const int WINDOW_HEIGHT{ Constants::TILE_SIZE * 7 };                           // height of the window
    const int SCROLL_SPEED{ Constants::TILE_SIZE / 10 / (Game::currentFps / 30) }; // scroll speed

    const int FONT_SIZE{ 20 };                                          // font size for message box text

    enum class State {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    Game::State currentState{ Game::State::TITLE_SCREEN };              // determines which set of functions to use

    bool isRunning{ false };                                            // determines whether the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Event event{};
    Mix_Music *music{ nullptr };
    SDL_Texture *text{ nullptr };
    SDL_Texture *logo{ nullptr };
    TTF_Font *font{ nullptr };

    const std::array<std::function<void()>, 3ULL> HANDLE_FUNCTIONS{
            [this]() -> void { this->handleTitleScreenEvents(); },
            [this]() -> void { this->handleOverworldEvents(); },
            [this]() -> void { this->handleBattleEvents(); }
    };

    const std::array<std::function<void()>, 3ULL> UPDATE_FUNCTIONS{
            [this]() -> void { this->updateTitleScreen(); },
            [this]() -> void { this->updateOverworld(); },
            [this]() -> void { this->updateBattle(); }
    };

    const std::array<std::function<void()>, 3ULL> RENDER_FUNCTIONS{
            [this]() -> void { this->renderTitleScreen(); },
            [this]() -> void { this->renderOverworld(); },
            [this]() -> void { this->renderBattle(); }
    };

    std::array<Map, 3ULL> maps{
            Map("Route 1", "Route1", 19, 14),
            Map("Route 2", "RivalBattle", 27, 24),
            Map("Route 3", "GymBattle", 27, 15)
    };

    int currentMapIndex{ 0 };
    Map *currentMap{ nullptr };

    void handleTitleScreenEvents();

    void updateTitleScreen();

    void renderTitleScreen();

    void handleOverworldEvents();

    void updateOverworld();

    void renderOverworld();

    void handleBattleEvents();

    void updateBattle();

    void renderBattle();

    void initializeGame();

    void updateTrainers() const;

    void checkForOpponents();

    void renderTextBox(const std::string &message);

    void changeMap(const std::tuple<int, int, Map::Id> &data);

    void saveData();

    void loadData();

    Game();

public:
    static Game &getInstance();

    ~Game();

    Game(const Game &) = delete;

    Game(Game &&) noexcept = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(Game &&) noexcept = delete;

    void handleEvents();

    void update();

    void render();

    [[nodiscard]] int getFps() const;

    explicit operator bool() const;
};
