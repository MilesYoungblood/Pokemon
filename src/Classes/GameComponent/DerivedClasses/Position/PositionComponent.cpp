//
// Created by Miles Youngblood on 12/3/2023.
//

#include "PositionComponent.h"

PositionComponent::PositionComponent(int x, int y) : x(x), y(y) {}

void PositionComponent::translateX(int amount) {
    this->x += amount;
}

void PositionComponent::translateY(int amount) {
    this->y += amount;
}

void PositionComponent::setPosition(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

int PositionComponent::getX() const {
    return this->x;
}

int PositionComponent::getY() const {
    return this->y;
}
