//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

namespace Camera {
    constexpr static int HEIGHT = TILE_SIZE * 7;     // height of the window
    constexpr static int WIDTH = TILE_SIZE * 9;      // width of the window

    static int xPos = 0;
    static int yPos = 0;

    inline void shiftUp(int distance) {
        yPos -= distance;
    }

    inline void shiftDown(int distance) {
        yPos += distance;
    }

    inline void shiftLeft(int distance) {
        xPos -= distance;
    }

    inline void shiftRight(int distance) {
        xPos += distance;
    }

    // returns whether an entity is in view of the camera,
    // thus enabling the rendering of only necessary objects
    inline bool isInView(const SDL_Rect *rect) {
        SDL_Rect r{ xPos, yPos, WIDTH, HEIGHT };
        return SDL_HasIntersection(rect, &r);
    }
}