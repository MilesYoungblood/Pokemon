//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

class Camera {
private:
    SDL_Rect view{ 0, 0, 0, 0 };

    Camera() = default;

public:
    inline static Camera &getInstance() {
        static Camera camera;
        return camera;
    }

    /// \brief Initializes the Camera's view
    /// \details This function takes in the Game's width
    /// and height as parameters and updates the Camera's
    /// view. This design choice is so the Game window's
    /// width and height remain consistent.
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

    /// \brief Determines whether a rectangle is in view of the camera
    /// \details This function's purpose is to enable the rendering of only
    /// necessary objects. It is useless to render objects that are not
    /// onscreen, not to mention costly. This function eliminates this problem.
    /// \param rect the rectangle to check
    /// \return true if the rectangle is in view, false otherwise
    [[nodiscard]] bool isInView(const SDL_Rect &rect) const {
        return SDL_HasIntersection(&rect, &this->view) == SDL_bool::SDL_TRUE;
    }

    /// \brief Finds the player's current position on the screen,
    /// then shifts everything, including the player, accordingly.
    /// \param p the player
    /// \param instructions a lambda that makes the map shift
    void lockOnPlayer(void (*instructions)(Direction, int)) const {
        // x-distance of the player from the center of the screen
        const int x_from_center = ((this->view.w - TILE_SIZE) / 2) - Player::getPlayer().getX() * TILE_SIZE;
        // y-distance of the player from the center of the screen
        const int y_from_center = ((this->view.h - TILE_SIZE) / 2) - Player::getPlayer().getY() * TILE_SIZE;

        Player::getPlayer().shiftHorizontally(x_from_center);
        Player::getPlayer().shiftVertically(y_from_center);

        // determines whether to shift left or right
        const Direction x_direction = x_from_center > 0 ? Direction::RIGHT : Direction::LEFT;
        // determines whether to shift up or down
        const Direction y_direction = y_from_center > 0 ? Direction::DOWN : Direction::UP;

        instructions(x_direction, x_direction == Direction::RIGHT ? x_from_center : -x_from_center);
        instructions(y_direction, y_direction == Direction::DOWN ? y_from_center : -y_from_center);
    }
};
