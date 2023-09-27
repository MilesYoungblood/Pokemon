//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include "../NPC/NPC.h"

class Map {
private:
    enum tiles { FREE = 0, OBSTRUCTION = 1, GRASS = 2 };

    struct ExitPoint {
        int x;                              // x-coordinate of the exit spot
        int y;                              // y-coordinate of the exit spot
        int newMap;                         // map that this exit point leads to
        int newX;                           // the player's new x-coordinates
        int newY;                           // the player's new y-coordinates
    };

    int width;                              // width of the map
    int height;                             // height of the map

    std::string name;

    std::vector<std::vector<int>> layout;   // The map is represented by a 2D int vector
                                            // values are represented by the tiles enum

    std::vector<NPC> npcArray;              // the set of trainers in this map

    std::vector<ExitPoint> exitPoints;      // coordinates where the player can leave this map to enter another

    void setBorders(const Map * from);
    bool isNPCHere(int x, int y) const;

public:
    Map(const char * name, int width, int height, const std::vector<ExitPoint> &exitPoints);
    Map(const char * name, int width, int height, const std::vector<NPC> &npcArray, const std::vector<ExitPoint> &exitPoints);
    Map(const Map &toCopy);
    Map& operator=(const Map &rhs);

    bool isObstructionHere(int x, int y) const;
    std::pair<std::pair<int, int>, int> isExitPointHere(int x, int y) const;
    int numNPCs();
    NPC& operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer &trainer) const;
};