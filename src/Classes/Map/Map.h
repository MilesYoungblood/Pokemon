//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include "../Player/Player.h"
#include "../../Namespaces/Camera/Camera.h"

class Map {
private:
    enum TileID {
        FREE,
        OBSTRUCTION,
        GRASS,
        TALL_GRASS __attribute__((unused)),
        WATER __attribute__((unused))
    };

    class Tile {
    private:
        TileID id;
        SDL_Rect dest;

    public:
        Tile() = default;
        Tile(TileID id, int x, int y) : id(id), dest({ x, y, TILE_SIZE, TILE_SIZE }) {}

        void update(int x, int y);

        [[nodiscard]] auto getRect() const -> SDL_Rect { return this->dest; }
        [[nodiscard]] auto getX() const -> int { return this->dest.x; }
        [[nodiscard]] auto getY() const -> int { return this->dest.y; }

        void setID(TileID newID) { this->id = newID; }
        [[nodiscard]] auto getID() const -> TileID { return this->id; }
    };

    struct ExitPoint {
        const int x;                                // x-coordinate of the exit spot
        const int y;                                // y-coordinate of the exit spot
        const int newMap;                           // map that this exit point leads to
        const int newX;                             // the player's new x-coordinates
        const int newY;                             // the player's new y-coordinates
    };

    const char *name;                               // name of the map

    const int width;                                // width of the map
    const int height;                               // height of the map

    static SDL_Texture *free;
    static SDL_Texture *obstruction;
    static SDL_Texture *grass;
    static SDL_Texture *tallGrass;
    static SDL_Texture *water;

    std::vector<std::vector<Map::Tile>> layout;     // The map is represented by a 2D Tile vector

    std::vector<Trainer *> trainers;                 // the set of trainers in this map

    std::vector<Map::ExitPoint> exitPoints;         // coordinates where the player can leave this map to enter another

    [[nodiscard]] auto isTrainerHere(int x, int y) const -> bool;

public:
    Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints, const std::initializer_list<Trainer *> &trainerList);
    Map(const Map &) = delete;
    auto operator=(const Map &) -> Map& = delete;
    Map(const Map &&) = delete;
    auto operator=(const Map &&) -> Map& = delete;
    ~Map();

    [[nodiscard]] auto isObstructionHere(int x, int y) const -> bool;
    [[nodiscard]] auto isExitPointHere(int x, int y) const -> std::array<int, 3>;

    [[nodiscard]] auto numTrainers() const -> int;
    auto operator[](int index) -> Trainer&;
    auto operator[](int index) const -> const Trainer&;

    void setObstruction(int x, int y);

    void updateMap(int distance, int flag);
    void renderMap();
    void resetMap();
};
