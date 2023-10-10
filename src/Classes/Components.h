//
// Created by Miles on 10/9/2023.
//

#pragma once

#include "ESC.h"

class PositionComponent : public Component {
private:
    int x;
    int y;

public:
    int getX() const { return this->x; }
    int getY() const { return this->y; }

    void init() override {
        this->x = 0;
        this->y = 0;
    }

    void update() override {

    }

    void setPosition(int newX, int newY) {
        this->x = newX;
        this->y = newY;
    }
};