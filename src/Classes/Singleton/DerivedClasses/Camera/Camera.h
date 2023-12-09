//
// Created by Miles Youngblood on 10/11/2023.
//

#pragma once

#include "../../../Entity/DerivedClasses/Trainer/DerivedClasses/Player/Player.h"

class Map;

class Camera : public Singleton<Camera> {
private:
    SDL_Rect view{ 0, 0, 0, 0 };

    friend class Singleton<Camera>;

    Camera() = default;

public:
    /// \brief Initializes the Camera's view
    /// \details This function takes in the Game's width
    /// and height as parameters and updates the Camera's
    /// view. This design choice is so the Game window's
    /// width and height remain consistent.
    /// \param w window width
    /// \param h window height
    void init(int w, int h);

    /// \brief Determines whether a rectangle is in view of the camera
    /// \details This function's purpose is to enable the rendering of only
    /// necessary objects. It is useless to render objects that are not
    /// onscreen, not to mention costly. This function eliminates this problem.
    /// \param rect the rectangle to check
    /// \return true if the rectangle is in view, false otherwise
    [[nodiscard]] bool isInView(const SDL_Rect &rect) const;

    /// \brief Finds the player's current position on the screen,
    /// then shifts everything, including the player, accordingly.
    /// \param instructions a lambda that makes the map shift
    void lockOnPlayer(Map *map) const;
};
