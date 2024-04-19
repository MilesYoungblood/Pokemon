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
    void addPokemon(std::unique_ptr<Pokemon> pokemon);

    /// \brief Removes a Pokemon from the party
    /// \param index of the party
    void removePokemon(long long int index);

    /// \brief Swaps Pokemon in the party
    /// \param a first
    /// \param b second
    void swapPokemon(std::size_t a, std::size_t b);

    /// \brief Getter for a Pokemon in the party
    /// \param index of the party
    /// \return a reference to the Pokemon
    Pokemon &operator[](std::size_t index) const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the beginning of the party
    std::vector<std::unique_ptr<Pokemon>>::iterator begin();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the beginning of the party
    [[nodiscard]] std::vector<std::unique_ptr<Pokemon>>::const_iterator begin() const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the end of the party
    std::vector<std::unique_ptr<Pokemon>>::iterator end();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the end of the party
    [[nodiscard]] std::vector<std::unique_ptr<Pokemon>>::const_iterator end() const;

    /// \brief Getter for party size
    /// \return party size
    [[nodiscard]] std::size_t partySize() const;

    /// \bried Overrides Character::handleFaint
    void handleFaint() override;

    /// \brief Overrides Character::handleSwitchOut
    /// \param renderFlag will be set back to true after the switch out is made
    void handleSwitchOut(bool &renderFlag) override;

    /// \brief Overrides Character::handleVictory
    void handleVictory() override;

    /// \brief Overrides Character::getDefeatMessage
    /// \return the victory message
    [[nodiscard]] std::vector<std::string> getDefeatMessage() const override;

    /// \brief Overrides Character::getAttacker
    /// \return the attacking Pokemon
    Pokemon *getAttacker() override;

    /// \brief Overrides Character::getAttacker
    /// return the attacking Pokemon
    [[nodiscard]] const Pokemon *getAttacker() const override;

    /// \brief Overrides Character::canFight
    /// \return true if the trainer can fight and false otherwise
    [[nodiscard]] bool canFight() const override;

    /// \brief Overrides Character::idle
    void idle() override;

protected:
    Trainer(const char *id, int x, int y, Direction direction, int vision);

private:
    enum : Uint8 {
        MAX_POKEMON = 6
    };

    bool keepLooping{ true };

    std::vector<std::unique_ptr<Pokemon>> party;
};
