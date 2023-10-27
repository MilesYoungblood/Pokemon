//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include "../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"
#include "../../Namespaces/Camera/Camera.h"

enum MapID {
    ROUTE_1,
    ROUTE_2,
    ROUTE_3
};

class Map {
private:
    enum TileID {
        FREE,
        OBSTRUCTION,
        GRASS,
        TALL_GRASS __attribute__((unused)),
        WATER __attribute__((unused))
    };

    struct Tile {
        TileID id;
        SDL_Rect dest;
    };

    struct ExitPoint {
        const int x;                                // x-coordinate of the exit spot
        const int y;                                // y-coordinate of the exit spot
        const int newMap;                           // map that this exit point leads to
        const int newX;                             // the player's new x-coordinates
        const int newY;                             // the player's new y-coordinates
    };

    const char *name{""};                               // name of the map

    const char *music{""};

    int width{0};                                // width of the map
    int height{0};                               // height of the map

    static SDL_Texture *free;
    static SDL_Texture *obstruction;
    static SDL_Texture *grass;
    static SDL_Texture *tallGrass;
    static SDL_Texture *water;

    std::vector<std::vector<Map::Tile>> layout;     // The map is represented by a 2D Tile vector

    std::vector<std::unique_ptr<Trainer>> trainers; // the set of trainers in this map

    std::vector<std::pair<std::pair<int, int>, std::unique_ptr<Item>>> items;

    std::vector<Map::ExitPoint> exitPoints;         // coordinates where the player can leave this map to enter another

    [[nodiscard]] bool isTrainerHere(int x, int y) const;

public:
    Map() = default;
    Map(const char *name, const char *music, int width, int height);
    Map(const char *name, const char *music, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char *name, const char *music, int width, int height, const std::vector<ExitPoint> &exitPoints, std::vector<std::unique_ptr<Trainer>> &trainerList);
    Map(const Map &) = delete;
    Map(const Map &&) = delete;
    Map & operator=(const Map &) = delete;
    Map & operator=(const Map &&) = delete;
    ~Map();

    [[nodiscard]] bool isObstructionHere(int x, int y) const;

    void addExitPoint(const ExitPoint &exitPoint);
    [[nodiscard]] std::array<int, 3> isExitPointHere(int x, int y) const;

    void addTrainer (std::unique_ptr<Trainer> toAdd);
    [[nodiscard]] int numTrainers() const;
    Trainer & operator[](int index);
    const Trainer & operator[](int index) const;

    [[nodiscard]] const char * getMusic() const;

    void setObstruction(int x, int y);

    void updateMap(Direction direction, int distance);
    void renderMap();
    void resetMap();
};
