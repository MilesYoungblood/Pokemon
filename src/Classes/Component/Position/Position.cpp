//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Position.h"

Project::Position::Position(int x, int y) : x(x), y(y) {}

void Project::Position::setPosition(int newX, int newY) {
    this->x = newX;
    this->y = newY;
}

void Project::Position::translateX(int t) {
    this->x += t;
}

void Project::Position::translateY(int t) {
    this->y += t;
}

int Project::Position::getX() const {
    return this->x;
}

int Project::Position::getY() const {
    return this->y;
}
