//
// Created by Miles on 10/1/2023.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "../../Classes/TextureManager/TextureManager.h"

class Entity {
protected:
    enum Direction { NORTH, EAST, SOUTH, WEST };

    int x;                                  // x-coordinate on map
    int y;                                  // y-coordinate on map
    int vision;                             // line of sight
    char model;                             // visual representation of which way the trainer is facing
    Entity::Direction direction;            // numerical representation of which way the trainer is facing

    static SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

public:
    Entity();
    Entity(int x, int y);
    Entity(int x, int y, const char *textureSheet, SDL_Renderer *r);
    Entity(const Entity &toCopy) = delete;
    Entity& operator=(const Entity &toCopy) = delete;
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
    Entity::Direction getDirection();

    void setCoordinates(int newX, int newY);
    int getX() const;
    int getY() const;

    char getModel() const;

    bool isFacingNorth() const;
    bool isFacingEast() const;
    bool isFacingSouth() const;
    bool isFacingWest() const;

    void face(const Entity *entity);

    bool isNextTo(const Entity *entity) const;
    bool hasVisionOf(const Entity *entity) const;

    void update(int x_pos, int y_pos);
    void render();

    SDL_Rect getRect() {
        return this->destRect;
    }
};
