//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../Graphic/DerivedClasses/Animation/Animation.h"

enum class Direction : Uint8 {
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
            throw std::invalid_argument(
                    std::string("Invalid argument: " + std::to_string(static_cast<int>(direction))) + " was passed");
    }
}

class Map;

class Entity {
public:
    enum class State : Uint8 {
        IDLE,
        WALKING,
        COLLIDING,
        FROZEN
    };

    Entity() = default;

    Entity(int x, int y);

    Entity(const char *name, int x, int y);

    Entity(const Entity &) = delete;

    Entity(Entity &&) noexcept = default;

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

    void setState(Entity::State state);

    [[nodiscard]] Entity::State getState() const;

    bool canMoveForward(const Map *map) const;

    bool isNextTo(const Entity *entity) const;

    bool hasVisionOf(const Entity *entity) const;

    void shiftHorizontally(int distance);

    void shiftVertically(int distance);

    void shift(Direction direction, int distance);

    [[nodiscard]] int getScreenX() const;

    [[nodiscard]] int getScreenY() const;

    void setAction(void (*function)(Entity *entity));

    void act();

    void updateAnimation();

    void render() const;

    void resetPos();

    [[nodiscard]] virtual bool canFight() const;

protected:
    void setVision(unsigned int newVision);

    void setAnimation(Direction direction, const char *path);

private:
    std::vector<std::string> dialogue;

    const char *name{ "" };

    int x{ 0 };                                           // x-coordinate on map
    int y{ 0 };                                           // y-coordinate on map
    int screenX{ 0 };                                     // x-coordinate on the screen
    int screenY{ 0 };                                     // y-coordinate on the screen
    unsigned int vision{ 1 };                             // line of sight

    Direction currentDirection{ Direction::DOWN };        // which way the trainer is facing
    Entity::State currentState{ Entity::State::IDLE };

    std::unordered_map<Direction, Animation> animations;

    void (*action)(Entity *){ nullptr };
};
