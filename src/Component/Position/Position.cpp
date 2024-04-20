//
// Created by Miles Youngblood on 4/14/2024.
//

#include "Position.h"

Component::Position::Position(const int x, const int y) : x(x), y(y) {}

void Component::Position::setPosition(const int x, const int y) {
    this->x = x;
    this->y = y;
}

void Component::Position::translateX(const int t) {
    this->x += t;
}

void Component::Position::translateY(const int t) {
    this->y += t;
}

void Component::Position::translate(const Direction d, const int t) {
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

int Component::Position::getX() const {
    return this->x;
}

int Component::Position::getY() const {
    return this->y;
}

bool Component::Position::isHere(const int xPos, const int yPos) const {
    return this->x == xPos and this->y == yPos;
}
