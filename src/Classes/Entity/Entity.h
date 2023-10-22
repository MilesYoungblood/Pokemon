//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/TextureManager/TextureManager.h"

const static int TILE_SIZE = 70;

enum Direction { NORTH, EAST, SOUTH, WEST };

class Map;

class Entity {
private:
    int x{0};                                           // x-coordinate on map
    int y{0};                                           // y-coordinate on map
    int vision{1};                                      // line of sight
    Direction direction{Direction::SOUTH};      // numerical representation of which way the trainer is facing

    SDL_Texture *frontModel{nullptr};                   // model of the entity when facing south
    SDL_Texture *backModel{nullptr};                    // model of the entity when facing north
    SDL_Texture *leftModel{nullptr};                    // model of the entity when facing west
    SDL_Texture *rightModel{nullptr};                   // model of the entity when facing east

    SDL_Texture *currentModel{nullptr};

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

    void moveForward();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    void setDirection(Direction newDirection);
    [[nodiscard]] auto getDirection() const -> Direction;

    void setCoordinates(int newX, int newY);
    [[nodiscard]] auto getX() const -> int;
    [[nodiscard]] auto getY() const -> int;

    [[nodiscard]] auto isFacingNorth() const -> bool;
    [[nodiscard]] auto isFacingEast() const -> bool;
    [[nodiscard]] auto isFacingSouth() const -> bool;
    [[nodiscard]] auto isFacingWest() const -> bool;

    void face(const Entity *entity);

    auto canMoveForward(const Map *map) -> bool;
    auto isNextTo(const Entity *entity) const -> bool;
    auto hasVisionOf(const Entity *entity) const -> bool;

    void setVision(int newVision);

    // these functions do NOT update the entity's internal coordinates
    // these functions merely update where the entity appears on in the window
    // these functions may later be incorporated into a camera rather than here
    void shiftUpOnMap(int distance);
    void shiftDownOnMap(int distance);
    void shiftLeftOnMap(int distance);
    void shiftRightOnMap(int distance);

    void shiftDirectionOnMap(Direction direct, int distance);
    
    [[nodiscard]] auto getRect() const -> SDL_Rect;

    void setFrontModel(SDL_Texture *newFrontModel);
    void setBackModel(SDL_Texture *newBackModel);
    void setLeftModel(SDL_Texture *newLeftModel);
    void setRightModel(SDL_Texture  *newRightModel);

    void setCurrentModel(SDL_Texture *newCurrentModel);

    auto getFrontModel() -> SDL_Texture *;

    void render();

    void resetPos();
};
