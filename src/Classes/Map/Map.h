//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include "../Player/Player.h"
#include "../Camera/Camera.h"

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
        explicit Tile(TileID id, int x, int y) : dest({ x, y, TILE_SIZE, TILE_SIZE }) {
            this->id = id;
        }

        void update(int x, int y) {
            this->dest.x = x;
            this->dest.y = y;
        }

        SDL_Rect *getRect() { return &this->dest; }
        [[nodiscard]] int getX() const { return this->dest.x; }
        [[nodiscard]] int getY() const { return this->dest.y; }

        void setID(TileID newID) { this->id = newID; }
        [[nodiscard]] TileID getID() const { return this->id; }
    };

    struct ExitPoint {
        const int x;                              // x-coordinate of the exit spot
        const int y;                              // y-coordinate of the exit spot
        const int newMap;                   // map that this exit point leads to
        const int newX;                     // the player's new x-coordinates
        const int newY;                     // the player's new y-coordinates
    };

    const char *name;                       // name of the map

    const int width;                        // width of the map
    const int height;                       // height of the map

    static SDL_Texture *free;
    static SDL_Texture *obstruction;
    static SDL_Texture *grass;
    static SDL_Texture *tallGrass;
    static SDL_Texture *water;

    std::vector<std::vector<Tile>> layout;  // The map is represented by a 2D int vector
                                            // values are represented by the tiles enum

    std::vector<Trainer*> trainers;         // the set of trainers in this map

    std::vector<Map::ExitPoint> exitPoints; // coordinates where the player can leave this map to enter another

    [[nodiscard]] bool isTrainerHere(int x, int y) const;

public:
    Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<ExitPoint> &exitPoints);
    Map(const Map &) = delete;
    Map& operator=(const Map &) = delete;
    ~Map();

    [[nodiscard]] bool isObstructionHere(int x, int y) const;
    [[nodiscard]] std::array<int, 3> isExitPointHere(int x, int y) const;

    [[nodiscard]] int numTrainers() const;
    Trainer& operator[](int index);
    const Trainer& operator[](int index) const;

    void setObstruction(int x, int y);

    void updateMap(int distance, int flag);
    void renderMap();

    void resetMap();
};
