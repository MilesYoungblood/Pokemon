//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../Character.h"
#include "../../../../../Move/Move.h"
#include "../../../../../../Enums/StatusCondition/StatusCondition.h"

class Pokemon : public Character {
public:
    enum class Stat : Uint8 {
        ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY, EVASIVENESS
    };

    enum : Uint8 {
        MAX_NUM_MOVES = 4
    };

    explicit Pokemon(const std::string &id);

    Pokemon(const std::string &id, const std::string &name, std::string gender, std::string ability, int level, int hp,
            int attack, int defense, int spAttack, int spDefense, int speed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&) noexcept = default;

    Pokemon &operator=(const Pokemon &) = default;

    Pokemon &operator=(Pokemon &&) noexcept = default;

    ~Pokemon() override = default;

    [[nodiscard]] int numMoves() const;

    void addMove(const std::string &id);

    void deleteMove(int index);

    void restoreHp(int amount);

    void takeDamage(int amount);

    [[nodiscard]] int getHp() const;

    [[nodiscard]] int getMaxHp() const;

    void initStatMods();

    void raiseStatMod(Pokemon::Stat stat, int amount);

    void lowerStatMod(Pokemon::Stat stat, int amount);

    [[nodiscard]] int getStatMod(Pokemon::Stat stat) const;

    [[nodiscard]] double getBaseStat(Pokemon::Stat stat) const;

    void setStatus(StatusCondition newStatus);

    [[nodiscard]] StatusCondition getStatus() const;

    void levelUp();

    [[nodiscard]] int getLevel() const;

    [[nodiscard]] std::string getGender() const;

    [[nodiscard]] std::string getAbility() const;

    [[nodiscard]] std::string getSpecies() const;

    [[nodiscard]] Type getType1() const;

    [[nodiscard]] Type getType2() const;

    [[nodiscard]] double getHeight() const;

    [[nodiscard]] double getWeight() const;

    [[nodiscard]] int getCatchRate() const;

    [[nodiscard]] bool isFainted() const;

    [[nodiscard]] bool isFullHp() const;

    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;

    [[nodiscard]] bool rivalsInSpeed(const Pokemon &pokemon) const;

    [[nodiscard]] bool isAfflicted() const;

    [[nodiscard]] bool canAttack() const;

    [[nodiscard]] std::string hpEmptyMessage() const;

    [[nodiscard]] std::string hpFullMessage() const;

    Move &operator[](int index);

    std::vector<std::unique_ptr<Move>>::iterator begin();

    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator begin() const;

    std::vector<std::unique_ptr<Move>>::iterator end();

    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator end() const;

private:
    int maxHp;
    int currentHp;

    std::array<int, 5> baseStats;
    std::array<int, 7> statModifiers;

    int level;

    std::vector<std::unique_ptr<Move>> moveSet;
    std::string ability;

    std::string gender;
    StatusCondition status{ StatusCondition::NONE };

    [[nodiscard]] double getStat(Pokemon::Stat stat) const;
};
