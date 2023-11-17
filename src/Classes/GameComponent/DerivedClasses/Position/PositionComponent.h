//
// Created by Miles Youngblood on 11/17/2023.
//

#pragma once

#include "../../GameComponent.h"

class PositionComponent : public GameComponent {
private:
    int x{ 0 };
    int y{ 0 };

public:
    PositionComponent() = default;

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
