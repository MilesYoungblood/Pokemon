//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

class Camera {
private:
    SDL_Rect view;

    Camera() : view({ 0, 0, 0, 0 }) {}

public:
    inline static Camera &getInstance() {
        static Camera camera;
        return camera;
    }

    /// Initializes the Camera's view
    /// \param w window width
    /// \param h window height
    void init(int w, int h) {
        static bool isInitialized = false;
        // only allow this function to be called once
        if (isInitialized) {
            return;
        }
        this->view.w = w;
        this->view.h = h;

        isInitialized = true;
    }

    /// Determines whether a rectangle is in view of the camera,
    /// thus enabling the rendering of only necessary objects.
    /// \param rect the rectangle to check
    /// \return SDL_True if the rectangle is in view, SDL_False otherwise
    [[nodiscard]] SDL_bool isInView(const SDL_Rect &rect) const {
        return SDL_HasIntersection(&rect, &this->view);
    }

    /// Finds the player's current position on the screen,
    /// then shifts everything, including the player, accordingly.
    /// \param p the player
    /// \param instructions a lambda that makes the map shift
    void lockOnPlayer(Player &p, void (*instructions)(Direction, int)) const {
        // x-distance of the player from the center of the screen
        const int x_from_center = ((this->view.w - TILE_SIZE) / 2) - p.getX() * TILE_SIZE;
        // y-distance of the player from the center of the screen
        const int y_from_center = ((this->view.h - TILE_SIZE) / 2) - p.getY() * TILE_SIZE;

        p.shiftHorizontally(x_from_center);
        p.shiftVertically(y_from_center);

        // determines whether to shift left or right
        const Direction x_direction = x_from_center > 0 ? Direction::RIGHT : Direction::LEFT;
        // determines whether to shift up or down
        const Direction y_direction = y_from_center > 0 ? Direction::DOWN : Direction::UP;

        instructions(x_direction, x_direction == Direction::RIGHT ? x_from_center : -x_from_center);
        instructions(y_direction, y_direction == Direction::DOWN ? y_from_center : -y_from_center);
    }
};
