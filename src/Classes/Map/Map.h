//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <windows.h>
#include "../Trainer/Trainer.h"

class Map {
private:
    enum Tile {
        FREE,
        OBSTRUCTION,
        GRASS,
        TALL_GRASS,
        WATER
    };

    struct ExitPoint {
        int x;                              // x-coordinate of the exit spot
        int y;                              // y-coordinate of the exit spot
        int newMap;                         // map that this exit point leads to
        int newX;                           // the player's new x-coordinates
        int newY;                           // the player's new y-coordinates
    };

    int width;                              // width of the map
    int height;                             // height of the map

    SDL_Rect dest;
    SDL_Rect src;

    SDL_Renderer *renderer;          // renderer
    SDL_Texture *free;
    SDL_Texture *obstruction;
    SDL_Texture *grass;
    static SDL_Texture *tallGrass;
    static SDL_Texture *water;

    std::string name;                       // name of the map

    std::vector<std::vector<Tile>> layout;  // The map is represented by a 2D int vector
                                            // values are represented by the tiles enum

    std::vector<Trainer*> trainers;         // the set of trainers in this map

    std::vector<ExitPoint> exitPoints;      // coordinates where the player can leave this map to enter another

    void setBorders(const Map * from);
    bool isTrainerHere(int x, int y) const;

public:
    Map(const char *name, int width, int height, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *r);
    Map(const char *name, int width, int height, const std::initializer_list<Trainer*> &trainerList, const std::vector<ExitPoint> &exitPoints, SDL_Renderer *renderer);
    Map(const Map &) = delete;
    Map& operator=(const Map &) = delete;
    ~Map();

    bool isObstructionHere(int x, int y) const;
    std::array<int, 3> isExitPointHere(int x, int y) const;

    int numNPCs();
    Trainer& operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer *player) const;
    void DrawMap();
};