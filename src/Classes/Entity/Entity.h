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
    Direction currentDirection{Direction::SOUTH};       // numerical representation of which way the trainer is facing

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
    Entity(const Entity &&) = delete;
    Entity & operator=(const Entity &) = delete;
    Entity & operator=(const Entity &&) = delete;
    ~Entity();

    void moveForward();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    void setDirection(Direction direction);
    [[nodiscard]] Direction getDirection() const;

    void setCoordinates(int newX, int newY);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;

    void face(const Entity *entity);
    [[nodiscard]] bool isFacingNorth() const;
    [[nodiscard]] bool isFacingEast() const;
    [[nodiscard]] bool isFacingSouth() const;
    [[nodiscard]] bool isFacingWest() const;

    bool canMoveForward(const Map *map) const;
    bool isNextTo(const Entity *entity) const;
    bool hasVisionOf(const Entity *entity) const;

    void setVision(int newVision);

    // these functions do NOT update the entity's internal coordinates
    // these functions merely update where the entity appears on in the window
    // these functions may later be incorporated into a camera rather than here
    void shiftUpOnMap(int distance);
    void shiftDownOnMap(int distance);
    void shiftLeftOnMap(int distance);
    void shiftRightOnMap(int distance);

    void shiftDirectionOnMap(Direction direction, int distance);
    
    [[nodiscard]] SDL_Rect getRect() const;

    void setFrontModel(SDL_Texture *newFrontModel);
    void setBackModel(SDL_Texture *newBackModel);
    void setLeftModel(SDL_Texture *newLeftModel);
    void setRightModel(SDL_Texture  *newRightModel);

    void setCurrentModel(SDL_Texture *newCurrentModel);

    SDL_Texture * getFrontModel();

    void render();

    void resetPos();
};
