//
// Created by Miles Youngblood on 3/9/2024.
//

#pragma once

#include "../Component/Position/Position.h"

class Entity {
public:
    Entity(const char *id, int x, int y);

    Entity(const Entity &) = default;

    Entity(Entity &&) noexcept = default;

    Entity &operator=(const Entity &) = default;

    Entity &operator=(Entity &&) noexcept = default;

    virtual ~Entity() = default;

    /// \brief Getter for id
    /// \return the entity's id
    [[nodiscard]] std::string getId() const;

    /// \brief Getter for map position
    /// \return the entity's map position
    Component::Position &getMapPosition();

    /// \brief Getter for map position
    /// \return the entity's map position
    [[nodiscard]] Component::Position getMapPosition() const;

    /// \brief Getter for screen position
    /// \return the entity's screen position
    Component::Position &getScreenPosition();

    /// \brief Getter for screen position
    /// \return the entity's screen position
    [[nodiscard]] Component::Position getScreenPosition() const;

    /// \brief Checks to see if this is next to an entity on the map
    /// \param entity to check
    /// \return true if this is next to the entity and false otherwise
    bool isNextTo(const Entity *entity) const;

    /// \brief Getter for sprite key
    /// \return the respective sprite key
    [[nodiscard]] virtual std::string getKey() const = 0;

    /// \brief Interacts with the entity
    virtual void interact() = 0;

    /// \brief Updates the entity
    virtual void update() = 0;

    /// \brief Renders the entity
    virtual void render(SDL_Texture *sprite) const = 0;

private:
    std::string id;

    Component::Position map;
    Component::Position screen;
};
