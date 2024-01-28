//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../../Map/Map.h"
#include "../../../Stopwatch/Stopwatch.h"
#include "../KeyManager/KeyManager.h"
#include "../Mixer/Mixer.h"
#include "../GraphicsEngine/GraphicsEngine.h"

extern std::unordered_map<std::unique_ptr<Trainer> *, int> pixelsTraveled;         // measures how many screen pixels a trainer has moved
extern std::unordered_map<std::unique_ptr<Trainer> *, bool> keepLooping;
extern Stopwatch keyDelay;

class State {
protected:
    State() = default;

public:
    State(const State &) = default;

    State(State &&) noexcept = default;

    State &operator=(const State &) = default;

    State &operator=(State &&) noexcept = default;

    virtual ~State() = default;

    virtual void update() = 0;

    virtual void render() = 0;
};

class TitleScreen : public State, public Singleton<TitleScreen> {
private:
    //TitleScreen() = default;

public:
    void update() override {

    }

    void render() override {

    }
};

class Overworld : public State, public Singleton<Overworld> {
private:
    //Overworld() = default;

public:
    void update() override {

    }

    void render() override {

    }
};

class BattlePhase : public State, public Singleton<BattlePhase> {
private:
    //BattlePhase() = default;

public:
    void update() override {

    }

    void render() override {

    }
};

class Game : public Singleton<Game> {
private:
    const std::array<int, 2> FPS{ 30, 60 };
    int currentFps{ FPS[1] };

    const int WINDOW_WIDTH{ Constants::TILE_SIZE * 9 };                            // width of the window
    const int WINDOW_HEIGHT{ Constants::TILE_SIZE * 7 };                           // height of the window
    const int SCROLL_SPEED{ Constants::TILE_SIZE / 10 / (this->currentFps / 30) }; // scroll speed

    const int FONT_SIZE{ Constants::TILE_SIZE / 4 };                               // font size for message box text

    std::array<std::unique_ptr<State>, 3> states{
            std::make_unique<TitleScreen>(TitleScreen::getInstance()),
            std::make_unique<Overworld>(Overworld::getInstance()),
            std::make_unique<BattlePhase>(BattlePhase::getInstance())
    };

    enum class State : Uint8 {
        TITLE_SCREEN, OVERWORLD, BATTLE
    };

    Game::State currentState{ Game::State::TITLE_SCREEN };              // determines which set of functions to use

    bool running{ false };                                              // determines whether the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Event event{};
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

    std::array<Map, 1> maps{
        Map("Nuvema Town")
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

    void render() const;

    [[nodiscard]] int getFps() const;

    [[nodiscard]] bool isRunning() const;

    void renderMain();
};
