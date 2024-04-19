//
// Created by Miles on 10/2/2023.
//

#pragma once

#include "../../Trainer.h"

class Player final : public Trainer {
public:
    static Player &getPlayer();

    /// \brief Adds a Pokemon to the player's pc
    /// \param toAdd the pokemon to add
    [[maybe_unused]] void addToPc(std::unique_ptr<Pokemon> toAdd);

    /// \brief Getter for number of items
    /// \tparam I Item type
    /// \return number of items of this type
    template<typename I>
    [[nodiscard]] std::size_t getNumItems() const {
        try {
            return this->inventory.at(typeid(I).hash_code()).size();
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item count: ") + e.what() + '\n');
        }
    }

    /// \brief Getter for an item
    /// \tparam I Item type
    /// \param id name of the item
    /// \return a reference to the item
    template<typename I>
    I &getItem(const std::string &id) {
        try {
            return *dynamic_cast<I *>(this->inventory.at(typeid(I).hash_code()).at(id).get());
        }
        catch (const std::exception &e) {
            throw std::runtime_error(std::string("Unable to retrieve item: ") + e.what() + '\n');
        }
    }

    /// \brief Constructs and adds an item by the lookup table
    /// \param id of the item
    /// \param n quantity
    void addItem(const std::string &id, int n);

    /// \brief Adds an item by moving
    /// \param item the item
    void addItem(std::unique_ptr<Item> item);

    /// \brief Removes an item from the inventory
    /// \tparam I Item type
    /// \param id of the item
    template<typename I>
    void removeItem(const std::string &id) {
        try {
            this->inventory.at(typeid(I).hash_code()).erase(id);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    /// \brief Checker to see if the player can move forward
    /// \param map the map
    /// \return true if the player can move forward and false otherwise
    [[nodiscard]] bool canMoveForward(const Map &map) const override;

    /// \brief Overrides Character::handleFaint
    void handleFaint() override;

    /// \brief Overrides Character::handleSwitchOut
    void handleSwitchOut(bool &renderFlag) override;

    /// \brief Overrides Character::handleVictory
    void handleVictory() override;

    /// \brief Overrides Character::getDefeatMessage
    [[nodiscard]] std::vector<std::string> getDefeatMessage() const override;

    /// \brief Overrides Character::canFight
    [[nodiscard]] bool canFight() const override;

private:
    enum : Uint8 {
        NUM_BOXES = 12,
        ROWS_PER_BOX = 5,
        COLS_PER_BOX = 6
    };

    std::array<Matrix<std::unique_ptr<Pokemon>>, NUM_BOXES> pc;

    std::unordered_map<std::size_t, std::unordered_map<std::string, std::unique_ptr<Item>>> inventory;

    int numFainted{ 0 };

    Player();

    void handleMove(SDL_Scancode scancode);

    void handleReturn() const;

    void interact() override;

    void walk() override;

    void idle() override;
};
