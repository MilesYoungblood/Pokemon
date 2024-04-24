//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../../Enums/StatusCondition/StatusCondition.h"
#include "../../../Move/Move.h"
#include "../Character.h"

class Pokemon final : public Character {
public:
    enum : Uint8 {
        MAX_NUM_MOVES = 4
    };

    explicit Pokemon(const char *id);

    Pokemon(const char *id, const char *name, std::string gender, std::string ability, int level, int hp,
            int attack, int defense, int spAttack, int spDefense, int speed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&) noexcept = delete;

    Pokemon &operator=(const Pokemon &) = delete;

    Pokemon &operator=(Pokemon &&) noexcept = delete;

    ~Pokemon() override = default;

    /// \brief Getter for number of moves
    /// \return the number of moves this Pokemon has
    [[nodiscard]] int numMoves() const;

    /// \brief Adds a move to the moveset
    /// \param id move id
    void learnMove(const std::string &id);

    /// \brief Removes a move from the moveset
    /// \param index move index
    void forgetMove(int index);

    /// \brief Getter for HP component
    /// \return the hp component
    Component::Resource &getHp();

    /// \brief Getter for HP component
    /// \return the hp component
    [[nodiscard]] Component::Resource getHp() const;

    /// \brief Getter for base stat
    /// \param x stat id
    /// \return the Pokemon's base stat at a given id
    [[nodiscard]] double getBaseStat(const std::string &x) const;

    /// \brief Setter for status condition
    /// \param x new status condition
    void setStatus(StatusCondition x);

    /// \brief Getter for status condition
    /// \return the status condition
    [[nodiscard]] StatusCondition getStatus() const;

    /// \brief Levels up the Pokemon
    void levelUp();

    /// \brief Getter for level
    /// \return the Pokemon's level
    [[nodiscard]] int getLevel() const;

    /// \brief Getter for gender
    /// \return the Pokemon's gender
    [[nodiscard]] std::string getGender() const;

    /// \brief Getter for ability id
    /// \return the ability id
    [[nodiscard]] std::string getAbility() const;

    /// \brief Getter for species
    /// \return the Pokemon's species
    [[nodiscard]] std::string getSpecies() const;

    /// \brief Getter for type1
    /// \return the Pokemon's first type
    [[nodiscard]] Type getType1() const;

    /// \brief the Getter for type2
    /// \return the Pokemon's second type if applicable
    [[nodiscard]] Type getType2() const;

    /// \brief Getter for height
    /// \return the Pokemon's height
    [[nodiscard]] double getHeight() const;

    /// \brief Getter for weight
    /// \return the Pokemon's weight
    [[nodiscard]] double getWeight() const;

    /// \brief Getter for catch rate
    /// \return the Pokemon's catch rate
    [[nodiscard]] int getCatchRate() const;

    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;

    [[nodiscard]] bool rivalsInSpeed(const Pokemon &pokemon) const;

    [[nodiscard]] bool isAfflicted() const;

    [[nodiscard]] bool canAttack() const;

    [[nodiscard]] std::string hpEmptyMessage() const;

    [[nodiscard]] std::string hpFullMessage() const;

    /// \brief Overrides Character::initMessage
    /// \return the initial message
    [[nodiscard]] std::string initMessage() const override;

    /// \brief Overrides Character::getAttacker
    /// \return the attacking Pokemon
    Pokemon *getAttacker() override;

    /// \brief Overrides Character::getAttacker
    /// \return the attacking Pokemon
    [[nodiscard]] const Pokemon *getAttacker() const override;

    /// \brief Overrides Character::canFight
    /// \return true if the Pokemon can fight
    [[nodiscard]] bool canFight() const override;

    /// \brief Getter for a move in the moveset
    /// \param index index in the moveset
    /// \return a reference to the move
    Move &operator[](int index) const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the beginning of the move vector
    std::vector<std::unique_ptr<Move>>::iterator begin();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the beginning of the party
    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator begin() const;

    /// \brief Allows for for-each loop functionality
    /// \return an iterator to the end of the move vector
    std::vector<std::unique_ptr<Move>>::iterator end();

    /// \brief Allows for for-each loop functionality
    /// \return a const iterator to the end of the move vector
    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator end() const;

private:
    static const std::unordered_map<std::string, std::pair<std::string, std::string>> natures;

    Component::Resource hp{};

    std::unordered_map<std::string, int> baseStats;

    int level;

    std::vector<std::unique_ptr<Move>> moveSet;
    std::string ability;

    std::string nature;
    std::string gender;

    StatusCondition status{ StatusCondition::NONE };
};
