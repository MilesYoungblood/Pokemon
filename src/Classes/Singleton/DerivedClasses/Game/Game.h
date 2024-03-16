//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../State/DerivedClasses/States.h"

class Game : public Singleton<Game> {
private:
    const std::array<int, 2> FPS{ 30, 60 };
    int currentFps{ FPS[1] };

    bool running{ false };                                                         // determines if the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };

    std::array<State *, 3> states{
            &State::getInstance<TitleScreen>(),
            &State::getInstance<Overworld>(),
            &State::getInstance<Battle>()
    };

    State *currentState{ this->states[static_cast<std::size_t>(State::Id::TITLE_SCREEN)] };

    friend class Singleton<Game>;

    Game();

public:
    enum : Uint16 {
        WINDOW_WIDTH = Map::TILE_SIZE * 9,
        WINDOW_HEIGHT = Map::TILE_SIZE * 7,
        FONT_SIZE = Map::TILE_SIZE / 4
    };

    ~Game() override;

    Game(const Game &) = delete;

    Game(Game &&) noexcept = delete;

    Game &operator=(const Game &) = delete;

    Game &operator=(Game &&) noexcept = delete;

    void handleEvents();

    void update();

    void render() const;

    void terminate();

    [[nodiscard]] int getFps() const;

    [[nodiscard]] bool isRunning() const;

    void setRenderColor(SDL_Color color);

    void setState(State::Id id);
};
