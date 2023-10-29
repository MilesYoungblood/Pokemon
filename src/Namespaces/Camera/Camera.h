//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

namespace Camera {
    constexpr static int HEIGHT = TILE_SIZE * 7;     // height of the window
    constexpr static int WIDTH = TILE_SIZE * 9;      // width of the window

    constexpr SDL_Rect r{ 0, 0, WIDTH, HEIGHT };

    // returns whether an entity is in view of the camera,
    // thus enabling the rendering of only the necessary objects
    inline SDL_bool isInView(const SDL_Rect &rect) {
        return SDL_HasIntersection(&rect, &r);
    }

    // finds the player's current position on the screen map,
    // then shifts everything, including the player, accordingly
    inline void lockOnPlayer(Player *p, void (*instructions)(Direction, int)) {
        // x-distance of the player from the center of the screen
        const int xFromCenter = ((WIDTH - TILE_SIZE) / 2) - p->getX() * TILE_SIZE;
        // y-distance of the player from the center of the screen
        const int yFromCenter = ((HEIGHT - TILE_SIZE) / 2) - p->getY() * TILE_SIZE;

        p->shiftHorizontally(xFromCenter);
        p->shiftVertically(yFromCenter);

        // determines whether to shift left or right
        const Direction xDirection = xFromCenter > 0 ? Direction::RIGHT : Direction::LEFT;
        // determines whether to shift up or down
        const Direction yDirection = yFromCenter > 0 ? Direction::DOWN : Direction::UP;

        instructions(xDirection, xDirection == Direction::RIGHT ? xFromCenter : -xFromCenter);
        instructions(yDirection, yDirection == Direction::DOWN ? yFromCenter : -yFromCenter);
    }
}
