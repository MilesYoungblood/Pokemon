//
// Created by Miles on 1/28/2024.
//

#pragma once

#include "../../State.h"
#include "../../../Singleton/Singleton.h"
#include "../../../Map/Map.h"

class Overworld : public State, public Singleton<Overworld> {
private:
    std::array<Map, 1> maps{
            Map("Nuvema Town")
    };

    std::size_t currentMapIndex{ 0 };
    Map *currentMap{ nullptr };

    int scrollSpeed = Map::TILE_SIZE / 20;

    friend class Singleton<Overworld>;

    Overworld() = default;

    void init();

public:
    void update() override;

    void render() override;

    void load();

    void save();

    void changeMap(const std::tuple<int, int, Map::Id> &data);

    [[nodiscard]] Map *getCurrentMap() const;

    [[nodiscard]] int getScrollSpeed() const;

    static void createTextBox(const std::vector<std::string> &messages);

    void handleMove(SDL_Scancode scancode);

    void handleReturn();
};
