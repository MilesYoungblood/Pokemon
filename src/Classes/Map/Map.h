//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <windows.h>
#include "../NPC/NPC.h"

class Map {
private:
    enum Tile { FREE, OBSTRUCTION, GRASS __attribute__((unused)), WATER __attribute__((unused)) };

    struct ExitPoint {
        int x;                              // x-coordinate of the exit spot
        int y;                              // y-coordinate of the exit spot
        int newMap;                         // map that this exit point leads to
        int newX;                           // the player's new x-coordinates
        int newY;                           // the player's new y-coordinates
    };

    int width;                              // width of the map
    int height;                             // height of the map

    std::string name;                       // name of the map

    std::vector<std::vector<Tile>> layout;  // The map is represented by a 2D int vector
                                            // values are represented by the tiles enum

    std::vector<NPC*> npcArray;             // the set of trainers in this map

    std::vector<ExitPoint> exitPoints;      // coordinates where the player can leave this map to enter another

    void setBorders(const Map * from);
    bool isNPCHere(int x, int y) const;

public:
    Map(const char * name, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char * name, int width, int height, const std::initializer_list<NPC*> &npcArray, const std::vector<ExitPoint> &exitPoints);
    Map(const Map &toCopy) = delete;
    Map& operator=(const Map &rhs) = delete;
    ~Map();

    bool isObstructionHere(int x, int y) const;
    std::array<int, 3> isExitPointHere(int x, int y) const;

    int numNPCs();
    NPC& operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer &trainer) const;
};