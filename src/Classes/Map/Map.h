//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <windows.h>
#include "../Trainer/Trainer.h"

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

    int getX() const { return this->dest.x; }
    int getY() const { return this->dest.y; }

    void setID(TileID newID) { this->id = newID; }

    TileID getID() const { return this->id; }
};

class Map {
private:
    struct ExitPoint {
        int x;                              // x-coordinate of the exit spot
        int y;                              // y-coordinate of the exit spot
        int newMap;                         // map that this exit point leads to
        int newX;                           // the player's new x-coordinates
        int newY;                           // the player's new y-coordinates
    };

    const char *name;                       // name of the map

    int width;                              // width of the map
    int height;                             // height of the map

    SDL_Rect dest;

    static SDL_Texture *free;
    static SDL_Texture *obstruction;
    static SDL_Texture *grass;
    static SDL_Texture *tallGrass;
    static SDL_Texture *water;

    std::vector<std::vector<Tile>> layout;  // The map is represented by a 2D int vector
                                            // values are represented by the tiles enum

    std::vector<Trainer*> trainers;         // the set of trainers in this map

    std::vector<Map::ExitPoint> exitPoints;      // coordinates where the player can leave this map to enter another

    void setBorders(const Map *from);
    bool isTrainerHere(int x, int y) const;

public:
    Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<ExitPoint> &exitPoints);
    Map(const Map &) = delete;
    Map& operator=(const Map &) = delete;
    ~Map();

    bool isObstructionHere(int x, int y) const;
    std::array<int, 3> isExitPointHere(int x, int y) const;

    int numNPCs();
    Trainer& operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer *player) const;

    Tile& getTile(int row, int column) { return this->layout[row][column]; }
    void UpdateMap(int newCoord, int flag);
    void DrawMap();
};