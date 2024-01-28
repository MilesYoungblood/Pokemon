//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../../Map/Map.h"
#include "../../../State/DerivedClasses/States.h"
#include "../../../Stopwatch/Stopwatch.h"
#include "../KeyManager/KeyManager.h"
#include "../Mixer/Mixer.h"
#include "../GraphicsEngine/GraphicsEngine.h"

extern std::unordered_map<Trainer *, int> pixelsTraveled;         // measures how many screen pixels a trainer has moved
extern std::unordered_map<Trainer *, bool> keepLooping;
extern Stopwatch keyDelay;

class Game : public Singleton<Game> {
private:
    const std::array<int, 2> FPS{ 30, 60 };
    int currentFps{ FPS[1] };

    const int WINDOW_WIDTH{ Constants::TILE_SIZE * 9 };                            // width of the window
    const int WINDOW_HEIGHT{ Constants::TILE_SIZE * 7 };                           // height of the window
    const int SCROLL_SPEED{ Constants::TILE_SIZE / 10 / (this->currentFps / 30) }; // scroll speed

    const int FONT_SIZE{ Constants::TILE_SIZE / 4 };                               // font size for message box text

    bool running{ false };                                                         // determines if the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Event event{};
    TTF_Font *font{ nullptr };

    std::array<std::unique_ptr<State>, 4> states{
            std::make_unique<TitleScreen>(TitleScreen::getInstance()),
            std::make_unique<Overworld>(Overworld::getInstance()),
            std::make_unique<BattlePhase>(BattlePhase::getInstance())
    };

    State::Id currentState{ State::Id::TITLE_SCREEN };                             // current state of the game

    std::array<Map, 1> maps{
            Map("Nuvema Town")
    };

    std::size_t currentMapIndex{ 0 };
    Map *currentMap{ nullptr };

    friend class Singleton<Game>;

    Game();

    void initializeGame();

public:
    ~Game() override;

    Game(const Game &) = delete;

    Game(Game &&) noexcept = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(Game &&) noexcept = delete;

    void handleEvents();

    void update();

    void render() const;

    void terminate();

    void saveData();

    void loadData();

    [[nodiscard]] int getFps() const;

    [[nodiscard]] bool isRunning() const;

    void setRenderColor(SDL_Color color);

    void setState(State::Id id);

    [[nodiscard]] int getScrollSpeed() const;

    [[nodiscard]] int getWindowWidth() const;

    [[nodiscard]] int getWindowHeight() const;

    [[nodiscard]] int getFontSize() const;

    [[nodiscard]] TTF_Font *getFont() const;

    void changeMap(std::size_t index);

    [[nodiscard]] Map *getCurrentMap() const;
};
