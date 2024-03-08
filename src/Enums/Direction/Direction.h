//
// Created by Miles Youngblood on 3/7/2024.
//

#pragma once

enum class Direction : Uint8 {
    UP, DOWN, LEFT, RIGHT
};

Direction oppositeDirection(Direction direction);