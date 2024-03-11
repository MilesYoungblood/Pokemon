//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"
#include "../../../../../Map/Map.h"

class Overworld : public State {
private:
    gsl::owner<Map *> currentMap{ nullptr };
    std::string currentMapId;

    int scrollSpeed{ Map::TILE_SIZE / 20 };

    friend class State;

    Overworld() = default;

public:
    Overworld(const Overworld &) = delete;

    Overworld(Overworld &&) noexcept = delete;

    Overworld &operator=(const Overworld &) = delete;

    Overworld &operator=(Overworld &&) noexcept = delete;

    ~Overworld() override;

    void init();

    void update() override;

    void render() override;

    void save();

    void changeMap(const std::tuple<int, int, std::string> &data);

    [[nodiscard]] gsl::owner<Map *> getCurrentMap() const;

    [[nodiscard]] int getScrollSpeed() const;

    static void createTextBox(const std::vector<std::string> &dialogue);

    void handleMove(SDL_Scancode scancode);

    void handleReturn();
};
