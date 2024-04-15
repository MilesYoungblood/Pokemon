//
// Created by Miles Youngblood on 6/13/2022.
//

#pragma once

#include "../../../Item/DerivedClasses/Items.h"

class Trainer : public Character {
public:
    Trainer(const char *id, const char *name, int x, int y, Direction direction, int vision);

    Trainer(const Trainer &) = delete;

    Trainer(Trainer &&toMove) noexcept = delete;

    Trainer &operator=(const Trainer &) = delete;

    Trainer &operator=(Trainer &&) noexcept = delete;

    ~Trainer() override = default;

    /// \brief Constructs and adds a Pokemon from the lookup table
    /// \param id Pokemon name
    void addPokemon(const char *id);

    /// \brief Adds a Pokemon by moving
    /// \param pokemon to add
    void addPokemon(Pokemon pokemon);

    /// \brief Removes a Pokemon from the party
    /// \param index of the party
    void removePokemon(long long int index);

    /// \brief Swaps Pokemon in the party
    /// \param a first
    /// \param b second
    void swapPokemon(std::size_t a, std::size_t b);

    /// \brief Getter for number of items
    /// \tparam I Item type
    /// \return number of items of this type
    template<typename I>
    [[nodiscard]] std::size_t getNumItems() const {
        try {
            return this->items.at(typeid(I).hash_code()).size();
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
            return *dynamic_cast<I *>(this->items.at(typeid(I).hash_code()).at(id).get());
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
    /// \param item
    void addItem(std::unique_ptr<Item> item);

    /// \brief Removes an item from the inventory
    /// \tparam I Item type
    /// \param id of the item
    template<typename I>
    void removeItem(const std::string &id) {
        try {
            this->items.at(typeid(I).hash_code()).erase(id);
        }
        catch (const std::out_of_range &e) {
            throw std::out_of_range(std::string("Error removing item: ") + e.what() + '\n');
        }
    }

    /// \brief Getter for a Pokemon in the party
    /// \param index of the party
    /// \return a reference to the Pokemon
    Pokemon &operator[](std::size_t index);

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the beginning of the party
    std::vector<Pokemon>::iterator begin();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the beginning of the party
    std::vector<Pokemon>::const_iterator begin() const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the end of the party
    std::vector<Pokemon>::iterator end();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the end of the party
    std::vector<Pokemon>::const_iterator end() const;

    /// \brief Getter for party size
    /// \return party size
    [[nodiscard]] std::size_t partySize() const;

    /// \brief Handles specific faint protocol
    virtual void handleFaint();

    /// \brief Handles specific victory protocol
    virtual void handleVictory();

    /// \brief Win message for a Trainer or the Player
    /// \param trainer pointer to the opponent trainer
    /// \return the win message
    [[nodiscard]] virtual std::vector<std::string> winMessage(const Trainer *trainer) const;

    /// \brief Overrides Character::canFight
    /// \return true if the trainer can fight and false otherwise
    [[nodiscard]] bool canFight() const override;

    /// \brief Overrides Character::isTrainer
    /// \return true
    [[nodiscard]] bool isTrainer() const override;

    /// \brief Overrides Character::idle
    void idle() override;

protected:
    Trainer(const char *id, int x, int y, Direction direction, int vision);

private:
    enum : Uint8 {
        MAX_POKEMON = 6
    };

    bool keepLooping{ true };

    std::vector<Pokemon> party;
    std::unordered_map<std::size_t, std::unordered_map<std::string, std::unique_ptr<Item>>> items;

    void init();
};
