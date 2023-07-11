//
// Created by Miles Youngblood on 7/10/2023.
//

#pragma once

#include <vector>
#include "../NPC/NPC.h"

class Map {
private:
    int xAxisLength;    // length of the x-axis of the map
    int yAxisLength;    // length of the y-axis of the map

    bool ** layout;     // map is represented by a 2D bool array
                        // A true at a coordinate denotes an obstruction
                        // A false at a coordinate denotes an open tile

    void createMap(const Map * from);
    void deleteMap();

public:
    Map(int x, int y);
    ~Map();
    Map& operator=(const Map &rhs);

    int getXBounds() const;
    int getYBounds() const;

    bool * operator[](int index);

    void setObstruction(int x, int y);
    void print(const Trainer &trainer, const std::vector<NPC> &npcArray) const;
};