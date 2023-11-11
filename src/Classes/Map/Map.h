//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Singletons/Camera/Camera.h"

class Map {
private:
    using inventory = std::vector<std::pair<std::pair<int, int>, std::unique_ptr<Item>>>;

    struct Tile {
        enum Id {
            GRASS,
            TALL_GRASS,
            OBSTRUCTION,
            WATER
        };
        Id id;
        int x;
        int y;
    };

    struct ExitPoint {
        int x;                                // x-coordinate of the exit spot
        int y;                                // y-coordinate of the exit spot
        int newMap;                           // map that this exit point leads to
        int newX;                             // the player's new x-coordinates
        int newY;                             // the player's new y-coordinates
    };

    const char *name{ "" };                         // name of the map

    const char *music{ "" };

    int width{ 0 };                                 // width of the map
    int height{ 0 };                                // height of the map

    inline static SDL_Texture *obstruction{ nullptr };
    inline static SDL_Texture *grass{ nullptr };
    inline static SDL_Texture *tallGrass{ nullptr };
    inline static Animation water;

    std::vector<std::vector<Map::Tile>> layout;     // The map is represented by a 2D Tile vector

    std::vector<std::unique_ptr<Trainer>> trainers; // the set of trainers in this map

    inventory items;

    std::vector<Map::ExitPoint> exitPoints;         // coordinates where the player can leave this map to enter another

    [[nodiscard]] bool isTrainerHere(int x, int y) const;

public:
    enum Id {
        ROUTE_1,
        ROUTE_2,
        ROUTE_3
    };

    Map() = default;

    Map(const char *name, const char *music, int width, int height);

    Map(const Map &rhs) = delete;

    Map(Map &&) = delete;

    Map &operator=(const Map &) = delete;

    Map &operator=(Map &&) noexcept;

    ~Map();

    static void initTextures();

    [[nodiscard]] bool isObstructionHere(int x, int y) const;

    void addExitPoint(const ExitPoint &exitPoint);

    [[nodiscard]] std::array<int, 3> isExitPointHere(int x, int y) const;

    void addTrainer(std::unique_ptr<Trainer> toAdd);

    [[nodiscard]] int numTrainers() const;

    Trainer &operator[](int index);

    const Trainer &operator[](int index) const;

    [[nodiscard]] const char *getMusic() const;

    void setObstruction(int x, int y);

    void shift(Direction direction, int distance);

    void render();

    void reset();
};
