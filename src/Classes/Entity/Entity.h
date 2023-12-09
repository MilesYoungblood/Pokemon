//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../Animation/Animation.h"

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

inline Direction oppositeDirection(Direction direction) {
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
            throw std::invalid_argument(std::string("Invalid argument: " + std::to_string(static_cast<int>(direction))) + " was passed");
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

    std::unordered_map<Direction, Animation> animations;

    void (*action)(Entity *){ nullptr };
    bool isLocked{ false };

public:
    Entity() = default;

    Entity(int x, int y);

    Entity(const char *name, int x, int y);

    Entity(const Entity &) = delete;

    Entity(Entity &&) noexcept = delete;

    Entity &operator=(const Entity &) = delete;

    Entity &operator=(Entity &&) noexcept = delete;

    virtual ~Entity() = default;

    void setName(const char *newName);

    [[nodiscard]] virtual std::string getName() const;

    void setDialogue(const char *text);

    void setDialogue(const std::vector<std::string> &text);

    [[nodiscard]] std::vector<std::string> getDialogue() const;

    void setCoordinates(int newX, int newY);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    void moveForward();

    void setDirection(Direction direction);

    [[nodiscard]] Direction getDirection() const;

    void face(const Entity *entity);

    [[nodiscard]] bool isFacing(Direction direction) const;

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

    void setAnimation(Direction direction, const char *path, int numFrames, int numRows);

    void setAction(void (*function)(Entity *entity));

    void lock();

    void unlock();

    void act();

    void updateAnimation();

    void render();

    void resetPos();

    [[nodiscard]] virtual bool canFight() const;
};
