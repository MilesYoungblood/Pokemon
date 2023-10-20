//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/TextureManager/TextureManager.h"

const static int TILE_SIZE = 70;

class Entity {
protected:
    enum Direction { NORTH, EAST, SOUTH, WEST };

    int x;                                  // x-coordinate on map
    int y;                                  // y-coordinate on map
    int vision;                             // line of sight
    Entity::Direction direction;            // numerical representation of which way the trainer is facing

    SDL_Texture *frontModel;                // model of the entity when facing south
    SDL_Texture *backModel;                 // model of the entity when facing north
    SDL_Texture *leftModel;                 // model of the entity when facing west
    SDL_Texture *rightModel;                // model of the entity when facing east

    SDL_Texture *currentTexture;

    SDL_Rect destRect;

public:
    Entity();
    Entity(int x, int y);
    Entity(const Entity &) = delete;
    auto operator=(const Entity &) -> Entity& = delete;
    Entity(const Entity &&) = delete;
    auto operator=(const Entity &&) ->Entity& = delete;
    ~Entity();

    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    void setDirection(Direction newDirection);
    auto getDirection() -> Entity::Direction;

    void setCoordinates(int newX, int newY);
    [[nodiscard]] auto getX() const -> int;
    [[nodiscard]] auto getY() const -> int;

    [[nodiscard]] auto isFacingNorth() const -> bool;
    [[nodiscard]] auto isFacingEast() const -> bool;
    [[nodiscard]] auto isFacingSouth() const -> bool;
    [[nodiscard]] auto isFacingWest() const -> bool;

    void face(const Entity *entity);

    auto isNextTo(const Entity *entity) const -> bool;
    auto hasVisionOf(const Entity *entity) const -> bool;

    // these functions do NOT update the entity's internal coordinates
    // these functions merely update where the entity appears on in the window
    // these functions may later be incorporated into a camera rather than here
    void shiftUpOnMap(int distance);
    void shiftDownOnMap(int distance);
    void shiftLeftOnMap(int distance);
    void shiftRightOnMap(int distance);
    
    [[nodiscard]] auto getRect() const -> SDL_Rect;

    void render();

    void resetPos();
};
