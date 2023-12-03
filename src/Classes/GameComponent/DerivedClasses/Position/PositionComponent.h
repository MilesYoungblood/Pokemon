//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../GameComponent.h"

class PositionComponent : public GameComponent {
private:
    int x;
    int y;

public:
    PositionComponent(int x, int y) : x(x), y(y) {}

    void translateX(int amount) {
        this->x += amount;
    }

    void translateY(int amount) {
        this->y += amount;
    }

    void setPosition(int newX, int newY) {
        this->x = newX;
        this->y = newY;
    }

    [[nodiscard]] int getX() const {
        return this->x;
    }

    [[nodiscard]] int getY() const {
        return this->y;
    }
};
