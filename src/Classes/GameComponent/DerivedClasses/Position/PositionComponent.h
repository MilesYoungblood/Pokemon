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
    PositionComponent(int x, int y);

    void translateX(int amount);

    void translateY(int amount);

    void setPosition(int newX, int newY);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;
};
