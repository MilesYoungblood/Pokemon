//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../../Map/Map.h"
#include "../../../Entity/Entity.h"

class Character : public Entity {
public:
    enum class State : Uint8 {
        IDLE,
        WALKING,
        COLLIDING,
        IMMOBILE
    };

    enum : Uint8 {
        WALK_SPEED = Map::TILE_SIZE / 20,
        RUN_SPEED [[maybe_unused]] = Map::TILE_SIZE / 10
    };

    Character(const char *id, int x, int y, Direction direction);

    Character(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Character(const Character &) = delete;

    Character(Character &&toMove) noexcept = delete;

    Character &operator=(const Character &) = delete;

    Character &operator=(Character &&) noexcept = delete;

    ~Character() override;

    void setName(const char *newName);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::string getId() const;

    void setDialogue(const std::vector<std::string> &text);

    [[nodiscard]] std::vector<std::string> getDialogue() const;

    void moveForward();

    void setDirection(Direction x);

    [[nodiscard]] Direction getDirection() const;

    void face(const Character *entity);

    [[nodiscard]] bool isFacing(Direction direction) const;

    void setState(Character::State x);

    [[nodiscard]] Character::State getState() const;

    [[nodiscard]] virtual bool canMoveForward(const Map &map) const;

    bool hasVisionOf(const Entity *entity) const;

    void makeAutonomous(const std::string &id);

    void interact() override;

    void updateAnimation();

    void update() override;

    void render() const override;

    [[nodiscard]] virtual bool canFight() const;

    [[nodiscard]] virtual bool isTrainer() const;

protected:
    Character(std::string id, std::string name);

    virtual void walk();

    void collide();

    virtual void idle();

    void incPixelCounter(int n);

    void resetPixelCounter();

    [[nodiscard]] int getPixelCounter() const;

private:
    std::vector<std::string> dialogue;

    std::string name;
    std::string id;

    unsigned int vision{ 1 };                                                   // line of sight

    std::atomic<Direction> currentDirection{ Direction::DOWN };              // which way the entity is facing
    std::atomic<Character::State> currentState{ Character::State::IDLE };    // dictates what the entity is doing

    int pixelCounter{ 0 };

    Sprite sprite;

    void decide();

    std::queue<void (*)(Character *)> decisions;

    std::thread autonomy;
    std::mutex mutex;
    std::condition_variable cv;
};
