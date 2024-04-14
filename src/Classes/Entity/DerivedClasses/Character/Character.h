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

    Character(const char *id, int x, int y, Direction direction, int vision);

    Character(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Character(const Character &) = delete;

    Character(Character &&toMove) noexcept = delete;

    Character &operator=(const Character &) = delete;

    Character &operator=(Character &&) noexcept = delete;

    ~Character() override;

    /// \brief Setter for name
    /// \param newName the new name
    void setName(const char *newName);

    /// \brief Getter for name
    /// \return the character's name
    [[nodiscard]] std::string getName() const;

    /// \brief Getter for id
    /// \return the character's id
    [[nodiscard]] std::string getId() const;

    /// \brief Setter for dialogue
    /// \param text the new text
    void setDialogue(const std::vector<std::string> &text);

    /// \brief Setter for state
    /// \param x the new state
    void setState(Character::State x);

    /// \brief Getter for state
    /// \return the character's state
    [[nodiscard]] Character::State getState() const;

    /// \brief Fires the character's decision making thread
    void gainAutonomy();

    /// \brief Overloads Entity::update
    void update() override;

    /// \brief Overloads Entity::render
    void render() const override;

protected:
    /// \brief Getter for dialogue
    /// \return the character's dialogue
    [[nodiscard]] std::vector<std::string> getDialogue() const;

    /// \brief Moves the character one tile in the direction it's facing
    void moveForward();

    /// \brief Setter for direction
    /// \param x the new direction
    void setDirection(Direction x);

    /// \brief Getter for direction
    /// \return the character's direction
    [[nodiscard]] Direction getDirection() const;

    /// \brief Faces the character the opposite direction of the parameter character
    /// \details This function does not face the character the direction in relation to where the parameter character is on the map
    /// \param character the character to face
    void face(const Character *character);

    /// \brief Checker for direction
    /// \param direction the direction
    /// \return true if the character's direction is the same as the parameter direction and false otherwise
    [[nodiscard]] bool isFacing(Direction direction) const;

    /// \brief Checks to see if the character can move forward
    /// \details Checks if the player, other entities, or collisions and other miscellaneous tiles are present
    /// \param map the map
    /// \return true if the character can move forward and false otherwise
    [[nodiscard]] virtual bool canMoveForward(const Map &map) const;

    /// \brief Checks for if the character has vision of an entity
    /// \param entity the entity
    /// \return true if the character can see the entity and false otherwise
    bool hasVisionOf(const Entity *entity) const;

    /// \brief Ceases autonomous decision making of an entity
    void loseAutonomy();

    /// \brief Overrides Entity::interact
    void interact() override;

    /// \brief Handles the character's walking protocol
    virtual void walk();

    /// \brief Handles the character's idling protocol
    virtual void idle();

    /// \brief Updates the character's sprite
    void updateAnimation();

    /// \brief Checker for if the character can fight
    /// \return true if the character can fight
    [[nodiscard]] virtual bool canFight() const;

    /// \brief Checker for if the trainer is a trainer
    /// \return false
    [[nodiscard]] virtual bool isTrainer() const;

    /// \brief Increments the character's pixel counter
    void incPixelCounter();

    /// \brief Resets the character's pixel counter back to zero
    void resetPixelCounter();

    /// \brief Getter for pixelCounter
    /// \return the character's pixelCounter
    [[nodiscard]] int getPixelCounter() const;

private:
    std::vector<std::string> dialogue;

    std::string name;
    std::string id;

    unsigned int vision;                                                      // line of sight
    int pixelCounter{ 0 };                                                    // counts how many pixels this has moved

    Direction currentDirection{ Direction::DOWN };                            // which way the entity is facing
    std::atomic<Character::State> currentState{ Character::State::IDLE };  // dictates what the entity is doing

    Sprite sprite;

    /// \brief Makes a decision
    /// \details pushes its decision to the desire queue to be called in the main thread
    void decide();

    std::queue<void (*)(Character *)> desires;

    std::atomic_bool autonomous{ false };
    std::thread autonomy;
    std::condition_variable cv;
};
