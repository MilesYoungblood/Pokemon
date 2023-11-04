//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Namespaces/TextureManager/TextureManager.h"
#include <vector>
#include <sstream>

inline const int TILE_SIZE = 80;

enum Direction { UP, DOWN, LEFT, RIGHT };

class Map;

class Entity {
private:
    std::vector<std::string> dialogue;

    const char *name;

    int x{0};                                           // x-coordinate on map
    int y{0};                                           // y-coordinate on map
    int screenX{0};                                     // x-coordinate on the screen
    int screenY{0};                                     // y-coordinate on the screen
    int vision{1};                                      // line of sight
    Direction currentDirection{Direction::DOWN};        // numerical representation of which way the trainer is facing

    SDL_Texture *frontModel{nullptr};                   // model of the entity when facing south
    SDL_Texture *backModel{nullptr};                    // model of the entity when facing north
    SDL_Texture *leftModel{nullptr};                    // model of the entity when facing west
    SDL_Texture *rightModel{nullptr};                   // model of the entity when facing east

    SDL_Texture *currentModel{nullptr};

    void (*action)(Entity *entity);

public:
    Entity(int x, int y);
    Entity(const char *name, int x, int y);
    Entity(const Entity &) = default;
    Entity(const Entity &&) = delete;
    Entity & operator=(const Entity &) = delete;
    Entity & operator=(const Entity &&) = delete;
    ~Entity();

    [[nodiscard]] std::string getName() const;

    void setDialogue(const char *text);
    [[nodiscard]] std::vector<std::string> getDialogue() const;

    void setCoordinates(int newX, int newY);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;

    void moveForward();

    void faceNorth();
    void faceEast();
    void faceSouth();
    void faceWest();

    void setDirection(Direction newDirection);
    [[nodiscard]] Direction getDirection() const;

    void face(const Entity *entity);
    [[nodiscard]] bool isFacingNorth() const;
    [[nodiscard]] bool isFacingEast() const;
    [[nodiscard]] bool isFacingSouth() const;
    [[nodiscard]] bool isFacingWest() const;

    bool canMoveForward(const Map *map) const;
    bool isNextTo(const Entity *entity) const;
    bool hasVisionOf(const Entity *entity) const;

    void setVision(int newVision);

    void shiftUpOnMap(int distance);
    void shiftDownOnMap(int distance);
    void shiftLeftOnMap(int distance);
    void shiftRightOnMap(int distance);

    void shiftHorizontally(int distance);
    void shiftVertically(int distance);

    void shiftDirectionOnMap(Direction direction, int distance);

    [[nodiscard]] int getScreenX() const;
    [[nodiscard]] int getScreenY() const;

    void setFrontModel(SDL_Texture *newFrontModel);
    void setBackModel(SDL_Texture *newBackModel);
    void setLeftModel(SDL_Texture *newLeftModel);
    void setRightModel(SDL_Texture  *newRightModel);

    void setCurrentModel(SDL_Texture *newCurrentModel);

    [[nodiscard]] SDL_Texture *getModel(Direction direction) const;

    void setAction(void (*function)(Entity *entity));

    void act(Entity *entity);

    void render();

    void resetPos();

    virtual explicit operator bool() const;
};
