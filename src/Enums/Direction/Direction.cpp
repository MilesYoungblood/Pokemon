//
// Created by Miles Youngblood on 3/7/2024.
//

#include "Direction.h"

Direction oppositeDirection(Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument(
                    std::string("Invalid argument: " + std::to_string(static_cast<int>(direction))) + " was passed");
    }
}
