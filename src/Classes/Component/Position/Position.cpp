//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Position.h"

Project::Position::Position(const int x, const int y) : x(x), y(y) {}

void Project::Position::setPosition(const int newX, const int newY) {
    this->x = newX;
    this->y = newY;
}

void Project::Position::translateX(const int t) {
    this->x += t;
}

void Project::Position::translateY(const int t) {
    this->y += t;
}

void Project::Position::translate(const Direction d, const int t) {
    switch (d) {
        case Direction::UP:
            this->y -= t;
            break;

        case Direction::DOWN:
            this->y += t;
            break;

        case Direction::LEFT:
            this->x -= t;
            break;

        case Direction::RIGHT:
            this->x += t;
    }
}

int Project::Position::getX() const {
    return this->x;
}

int Project::Position::getY() const {
    return this->y;
}

bool Project::Position::isHere(const int xPos, const int yPos) const {
    return this->x == xPos and this->y == yPos;
}
