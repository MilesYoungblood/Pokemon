//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include <algorithm>
#include <conio.h>
#include "../NPC/NPC.h"

class Map {
private:
    enum tiles { EMPTY = 0, GRASS = 1, EXIT = 2 };

    int width;                              // width of the map
    int height;                             // height of the map

    std::vector<std::vector<bool>> layout;  // The map is represented by a 2D bool array
                                            // A true at a coordinate denotes an obstruction
                                            // A false at a coordinate denotes an open tile

    std::vector<NPC> npcArray;              // the set of trainers in this map

    std::vector<std::pair<std::pair<int, int>, int>> exitPoints;   // coordinates where the player can leave this map
    // to enter another

    void createMap(const Map * from, bool copy);
    //void deleteMap();
    bool isNPCHere(int x, int y) const;

public:
    Map(int width, int height);
    Map(int width, int height, const std::vector<NPC> &npcArray);
    Map(int width, int height, const std::vector<NPC> &npcArray, const std::vector<std::pair<std::pair<int, int>, int>> &exitPoints);
    Map(const Map &toCopy);
    //~Map();
    Map& operator=(const Map &rhs);

    bool getTile(int x, int y) const;
    int isExitPointHere(int x, int y) const;
    int numNPCs();
    NPC& operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer &trainer) const;
};