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

    // returns whether an entity is in view of the camera,
    // thus enabling the rendering of only the necessary objects
    inline bool isInView(const SDL_Rect &rect) {
        SDL_Rect r{ xPos, yPos, WIDTH, HEIGHT };
        return SDL_HasIntersection(&rect, &r);
    }

    // finds the player's current position on the screen map,
    // then shifts everything, including the player, accordingly
    inline void lockOnPlayer(Player *p, void (*instructions)(int, int)) {
        xPos = 0;
        yPos = 0;

        int xFromCenter = ((WIDTH - TILE_SIZE) / 2) - p->getX() * TILE_SIZE;    // x-distance of the player from the center of the screen
        int yFromCenter = ((HEIGHT - TILE_SIZE) / 2) - p->getY() * TILE_SIZE;   // y-distance of the player from the center of the screen

        const int xDirection = xFromCenter > 0 ? 3 : 4;                         // determines whether to shift left or right
        const int yDirection = yFromCenter > 0 ? 1 : 2;                         // determines whether to shift up or down

        if (xDirection == 3) {
            p->shiftRightOnMap(xFromCenter);
            Camera::shiftRight(xFromCenter);
        }
        else {
            xFromCenter *= -1;
            p->shiftLeftOnMap(xFromCenter);
            Camera::shiftLeft(xFromCenter);
        }

        if (yDirection == 1) {
            p->shiftDownOnMap(yFromCenter);
            Camera::shiftDown(yFromCenter);
        }
        else {
            yFromCenter *= -1;
            p->shiftUpOnMap(yFromCenter);
            Camera::shiftUp(yFromCenter);
        }

        instructions(xFromCenter, xDirection);
        instructions(yFromCenter, yDirection);
    }
}
