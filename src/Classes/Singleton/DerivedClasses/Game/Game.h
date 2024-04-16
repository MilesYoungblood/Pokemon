//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../Scene/DerivedClasses/Scenes.h"

class Game final : public Singleton<Game> {
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

    void handleEvents() const;

    void update() const;

    void render() const;

    void terminate();

    [[nodiscard]] int getFps() const;

    [[nodiscard]] bool isRunning() const;

    void setRenderColor(SDL_Color color) const;

    void changeScene(Scene::Id id);

private:
    const std::array<int, 2> fps{ 30, 60 };
    int currentFps{ fps[1] };

    bool running{ false };                                                         // determines if the game is running

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };

    std::array<Scene *, 3> scenes{
        &Scene::getInstance<TitleScreen>(),
        &Scene::getInstance<Overworld>(),
        &Scene::getInstance<Battle>()
    };

    Scene *currentScene{ this->scenes[static_cast<std::size_t>(Scene::Id::TITLE_SCREEN)] };

    friend class Singleton;

    Game();
};
