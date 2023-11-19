//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Animation/Animation.h"

inline const int TILE_SIZE = 80;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

inline Direction oppositeDirection(const Direction direction) {
    switch (direction) {
        case Direction::UP:
            return Direction::DOWN;
        case Direction::RIGHT:
            return Direction::LEFT;
        case Direction::DOWN:
            return Direction::UP;
        case Direction::LEFT:
            return Direction::RIGHT;
        default:
            throw std::invalid_argument("Unexpected error: function oppositeDirection");
    }
}

class Map;

class Entity {
private:
    std::vector<std::string> dialogue;

    const char *name{ "" };

    int x{ 0 };                                           // x-coordinate on map
    int y{ 0 };                                           // y-coordinate on map
    int screenX{ 0 };                                     // x-coordinate on the screen
    int screenY{ 0 };                                     // y-coordinate on the screen
    int vision{ 1 };                                      // line of sight
    Direction currentDirection{ Direction::DOWN };        // numerical representation of which way the trainer is facing

    std::array<Animation, 4> animations;

    void (*action)(Entity *entity){ [](Entity *entity) -> void {} };

public:
    Entity() = default;

    Entity(int x, int y);

    Entity(const char *name, int x, int y);

    Entity(const Entity &) = delete;

    Entity(Entity &&) noexcept = delete;

    Entity &operator=(const Entity &) = delete;

    Entity &operator=(Entity &&) noexcept = delete;

    virtual ~Entity() = default;

    inline void setName(const char *newName) {
        this->name = newName;
    }

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

    inline void setUpAnimation(const char *path, int numFrames, int numRows) {
        this->animations[Direction::UP] = Animation(path, numFrames, numRows);
    }

    inline void setDownAnimation(const char *path, int numFrames, int numRows) {
        this->animations[Direction::DOWN] = Animation(path, numFrames, numRows);
    }

    inline void setLeftAnimation(const char *path, int numFrames, int numRows) {
        this->animations[Direction::LEFT] = Animation(path, numFrames, numRows);
    }

    inline void setRightAnimation(const char *path, int numFrames, int numRows) {
        this->animations[Direction::RIGHT] = Animation(path, numFrames, numRows);
    }

    inline void setAction(void (*function)(Entity *entity)) {
        this->action = function;
    }

    inline void act(Entity *entity) {
        this->action(entity);
    }

    inline void updateAnimation() {
        this->animations.at(this->currentDirection).update();
    }

    inline void render() {
        try {
            this->animations.at(this->currentDirection).render({ this->screenX, this->screenY, TILE_SIZE, TILE_SIZE });
        }
        catch (const std::out_of_range &e) {
            static int attempts = 1;
            std::clog << "(Attempt " << attempts++ << ") Error rendering animation: " << e.what() << '\n';
        }
    }

    inline void resetPos() {
        this->screenX = this->x * TILE_SIZE;
        this->screenY = this->y * TILE_SIZE;
    }

    virtual explicit operator bool() const;
};
