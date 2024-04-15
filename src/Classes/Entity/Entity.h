//
// Created by Miles Youngblood on 3/9/2024.
//

#pragma once

#include "../Component/Position/Position.h"

class Entity {
private:
    Project::Position map;
    Project::Position screen;

public:
    Entity(int x, int y);

    Entity(const Entity &) = default;

    Entity(Entity &&) noexcept = default;

    Entity &operator=(const Entity &) = default;

    Entity &operator=(Entity &&) noexcept = default;

    virtual ~Entity() = default;

    /// \brief Getter for map position
    /// \return the entity's map position
    Project::Position &getMapPosition();

    /// \brief Getter for map position
    /// \return the entity's map position
    [[nodiscard]] Project::Position getMapPosition() const;

    /// \brief Getter for screen position
    /// \return the entity's screen position
    Project::Position &getScreenPosition();

    /// \brief Getter for screen position
    /// \return the entity's screen position
    [[nodiscard]] Project::Position getScreenPosition() const;

    /// \brief Checks to see if this is next to an entity on the map
    /// \param entity to check
    /// \return true if this is next to the entity and false otherwise
    bool isNextTo(const Entity *entity) const;

    /// \brief Interacts with the entity
    virtual void interact() = 0;

    /// \brief Updates the entity
    virtual void update() = 0;

    /// \brief Renders the entity
    virtual void render() const = 0;
};
