//
// Created by Miles Youngblood on 3/9/2024.
//

#pragma once

#include "../../Enums/Direction/Direction.h"

class Entity {
private:
    std::atomic_int mapX{ 0 };                          // x-coordinate on map
    std::atomic_int mapY{ 0 };                          // y-coordinate on map
    std::atomic_int screenX{ 0 };                       // x-coordinate on the screen
    std::atomic_int screenY{ 0 };                       // y-coordinate on the screen

protected:
    Entity() = default;

    Entity(int x, int y);

public:
    Entity(const Entity &) = delete;

    Entity(Entity &&) noexcept = delete;

    Entity &operator=(const Entity &) = delete;

    Entity &operator=(Entity &&) noexcept = delete;

    virtual ~Entity() = default;

    /// \brief Sets the entity's map coordinates and screen coordinates
    /// \param x new x-coordinate on the map
    /// \param y new y-coordinate on the map
    void setCoordinates(int x, int y);

    /// \brief Translates the entity's x-coordinate by 1
    /// \param positive translate positively or negatively on plane
    void translateX(bool positive);

    /// \brief Translates the entity's y-coordinate by 1
    /// \param positive translate positively or negatively on plane
    void translateY(bool positive);

    /// \brief Getter for map x-coordinate
    /// \return x-coordinate on map
    [[nodiscard]] int getMapX() const;

    /// \brief Getter for map y-coordinate
    /// \return y-coordinate on map
    [[nodiscard]] int getMapY() const;

    /// \brief Checks to see if this is next to an entity on the map
    /// \param entity to check
    /// \return true if this is next to the entity and false otherwise
    bool isNextTo(const Entity *entity) const;

    /// \brief shifts this horizontally on the screen
    /// \param n distance
    void shiftHorizontally(int n);

    /// \brief shifts this vertically on the screen
    /// \param n distance
    void shiftVertically(int n);

    /// \brief shifts this some direction on the screen
    /// \param direction to shift
    /// \param n distance
    void shift(Direction direction, int n);

    /// \brief Getter for screen x coordinate
    /// \return screen x-coordinate
    [[nodiscard]] int getScreenX() const;

    /// \brief Getter for screen y coordinate
    /// \return screen y-coordinate
    [[nodiscard]] int getScreenY() const;

    /// \brief Interacts with the entity
    virtual void interact() = 0;

    /// \brief Updates the entity
    virtual void update() = 0;

    /// \brief Renders the entity
    virtual void render() const = 0;
};
