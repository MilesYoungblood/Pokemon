//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../../Map/Map.h"
#include "../../../Stopwatch/Stopwatch.h"
#include "../KeyManager/KeyManager.h"
#include "../SoundPlayer/SoundPlayer.h"
#include "../GraphicsEngine/GraphicsEngine.h"

extern std::unordered_map<std::unique_ptr<Trainer> *, int> pixelsTraveled;           // measures how many screen pixels a trainer has moved
extern std::unordered_map<std::unique_ptr<Trainer> *, bool> keepLooping;
extern Stopwatch<std::chrono::milliseconds> keyDelay;

class Game : public Singleton<Game> {
private:
    const std::array<int, 2> FPS{ 30, 60 };
    int currentFps{ FPS[1] };

    const int WINDOW_WIDTH{ Constants::TILE_SIZE * 9 };                            // width of the window
    const int WINDOW_HEIGHT{ Constants::TILE_SIZE * 7 };                           // height of the window
    const int SCROLL_SPEED{ Constants::TILE_SIZE / 10 / (Game::currentFps / 30) }; // scroll speed

    const int FONT_SIZE{ 20 };                                          // font size for message box text

    enum class State : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    Game::State currentState{ Game::State::TITLE_SCREEN };              // determines which set of functions to use

    bool running{ false };                                              // determines whether the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Event event{};
    Mix_Music *music{ nullptr };
    SDL_Texture *text{ nullptr };
    SDL_Texture *logo{ nullptr };
    TTF_Font *font{ nullptr };

    const std::array<std::function<void()>, 3> UPDATE_FUNCTIONS{
            [this] -> void { this->updateTitleScreen(); },
            [this] -> void { this->updateOverworld(); },
            [this] -> void { this->updateBattle(); }
    };

    const std::array<std::function<void()>, 3> RENDER_FUNCTIONS{
            [this] -> void { this->renderTitleScreen(); },
            [this] -> void { this->renderOverworld(); },
            Game::renderBattle
    };

    std::array<Map, 3> maps{
            Map(),
            Map("Route 2", "RivalBattle", 27, 24),
            Map("Route 3", "GymBattle", 27, 15)
    };

    std::size_t currentMapIndex{ 0 };
    Map *currentMap{ nullptr };

    friend class Singleton<Game>;

    Game();

    void updateTitleScreen();

    void renderTitleScreen();

    void updateOverworld();

    void renderOverworld();

    void updateBattle();

    static void renderBattle();

    void initializeGame();

    void createTextBox(const std::vector<std::string> &messages) const;

    void checkForOpponents();

    void changeMap(const std::tuple<int, int, Map::Id> &data);

    void saveData();

    void loadData();

public:
    ~Game() override;

    Game(const Game &) = delete;

    Game(Game &&) noexcept = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(Game &&) noexcept = delete;

    void handleEvents();

    void update();

    void render();

    [[nodiscard]] int getFps() const;

    [[nodiscard]] bool isRunning() const;

    void renderMain();
};
