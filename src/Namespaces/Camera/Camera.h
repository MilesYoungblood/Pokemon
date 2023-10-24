//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

namespace Camera {
    constexpr static int HEIGHT = TILE_SIZE * 7;     // height of the window
    constexpr static int WIDTH = TILE_SIZE * 9;      // width of the window

    static int xPos = 0;
    static int yPos = 0;

    inline void shiftUp(const int distance) {
        yPos -= distance;
    }

    inline void shiftDown(const int distance) {
        yPos += distance;
    }

    inline void shiftLeft(const int distance) {
        xPos -= distance;
    }

    inline void shiftRight(const int distance) {
        xPos += distance;
    }

    inline void shift(const Direction direction, const int distance) {
        switch (direction) {
            case NORTH:
                yPos -= distance;
            case EAST:
                xPos += distance;
            case SOUTH:
                yPos += distance;
            case WEST:
                xPos -= distance;
        }
    }

    // returns whether an entity is in view of the camera,
    // thus enabling the rendering of only the necessary objects
    inline SDL_bool isInView(const SDL_Rect &rect) {
        const SDL_Rect r{ xPos, yPos, WIDTH, HEIGHT };
        return SDL_HasIntersection(&rect, &r);
    }

    // finds the player's current position on the screen map,
    // then shifts everything, including the player, accordingly
    inline void lockOnPlayer(Player *p, void (*instructions)(Direction, int)) {
        xPos = 0;
        yPos = 0;

        int xFromCenter = ((WIDTH - TILE_SIZE) / 2) - p->getX() * TILE_SIZE;    // x-distance of the player from the center of the screen
        int yFromCenter = ((HEIGHT - TILE_SIZE) / 2) - p->getY() * TILE_SIZE;   // y-distance of the player from the center of the screen

        // determines whether to shift left or right
        const Direction xDirection = xFromCenter > 0 ? Direction::EAST : Direction::WEST;

        // determines whether to shift up or down
        const Direction yDirection = yFromCenter > 0 ? Direction::SOUTH : Direction::NORTH;

        if (xDirection == Direction::EAST) {
            p->shiftRightOnMap(xFromCenter);
            Camera::shiftRight(xFromCenter);
        }
        else {
            xFromCenter *= -1;
            p->shiftLeftOnMap(xFromCenter);
            Camera::shiftLeft(xFromCenter);
        }

        if (yDirection == Direction::SOUTH) {
            p->shiftDownOnMap(yFromCenter);
            Camera::shiftDown(yFromCenter);
        }
        else {
            yFromCenter *= -1;
            p->shiftUpOnMap(yFromCenter);
            Camera::shiftUp(yFromCenter);
        }

        instructions(xDirection, xFromCenter);
        instructions(yDirection, yFromCenter);
    }
}
