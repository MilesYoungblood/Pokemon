//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../../Entity/Entity.h"

class Map;

class Character : public Entity {
public:
    enum class State : Uint8 {
        IDLE,
        WALKING,
        COLLIDING,
        IMMOBILE
    };

    Character(const char *id, int x, int y, Direction direction);

    Character(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Character(const Character &) = delete;

    Character(Character &&toMove) noexcept = default;

    Character &operator=(const Character &) = delete;

    Character &operator=(Character &&) noexcept = delete;

    ~Character() override = default;

    static void init();

    static void clean();

    void setName(const char *newName);

    [[nodiscard]] virtual std::string getName() const;

    void setDialogue(const char *text);

    void setDialogue(const std::vector<std::string> &text);

    [[nodiscard]] std::vector<std::string> getDialogue() const;

    void moveForward();

    void setDirection(Direction direction);

    [[nodiscard]] Direction getDirection() const;

    void face(const Character *entity);

    [[nodiscard]] bool isFacing(Direction direction) const;

    void setState(Character::State state);

    [[nodiscard]] Character::State getState() const;

    [[nodiscard]] virtual bool canMoveForward(gsl::owner<Map *> map) const;

    bool hasVisionOf(const Entity *entity) const;

    void setAction(void (*function)(Character *entity));

    void interact() override;

    void updateAnimation();

    void update() override;

    void render() const override;

    [[nodiscard]] virtual bool canFight() const;

    [[nodiscard]] virtual bool isTrainer() const;

protected:
    Character() = default;

    virtual void walk();

    void collide();

    virtual void idle();

    void act();

    void incPixelCounter(int n);

    void resetPixelCounter();

    [[nodiscard]] int getWalkCounter() const;

private:
    std::vector<std::string> dialogue;

    std::string name;
    std::string id;

    unsigned int vision{ 1 };                                               // line of sight

    Direction currentDirection{ Direction::DOWN };                          // which way the entity is facing
    Character::State currentState{ Character::State::IDLE };                // dictates what the entity is doing

    int pixelCounter{ 0 };

    struct Sprite {
        struct Sheet {
            SDL_Texture *sprite{ nullptr };
            Uint32 numRows{ 0 };
            Uint32 numCols{ 0 };
        };
        int currentCol{ 0 };
        int currentRow{ 0 };
    };

    using spriteSet = std::array<Sprite::Sheet, 4>;
    inline static std::unordered_map<std::string, spriteSet> sprites;     // set of overworld sprites

    Sprite sprite;

    void (*action)(Character *entity){ nullptr };
};
