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
    int width;          // width of the map
    int height;         // height of the map

    bool ** layout;     // map is represented by a 2D bool array
                        // A true at a coordinate denotes an obstruction
                        // A false at a coordinate denotes an open tile

    void createMap(const Map * from);
    void deleteMap();

public:
    Map(int width, int height);
    Map(const Map &toCopy);
    ~Map();
    Map& operator=(const Map &rhs);

    int getWidth() const;
    int getHeight() const;

    bool getTile(int x, int y) const;
    bool * operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer &trainer, const std::vector<NPC> &npcArray) const;
};