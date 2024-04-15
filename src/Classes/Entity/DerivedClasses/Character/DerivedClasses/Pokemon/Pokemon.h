//
// Created by miles on 5/5/2022.
//

#pragma once

#include "../../../../../../Enums/StatusCondition/StatusCondition.h"
#include "../../../../../Component/Resource/Resource.h"
#include "../../../../../Move/Move.h"
#include "../../Character.h"

class Pokemon final : public Character {
public:
    enum class Stat : Uint8 {
        ATTACK, DEFENSE, SP_ATTACK, SP_DEFENSE, SPEED, ACCURACY, EVASIVENESS
    };

    enum : Uint8 {
        MAX_NUM_MOVES = 4
    };

    explicit Pokemon(const std::string &id);

    Pokemon(std::string id, std::string name, std::string gender, std::string ability, int level, int hp,
            int attack, int defense, int spAttack, int spDefense, int speed);

    Pokemon(const Pokemon &) = delete;

    Pokemon(Pokemon &&) noexcept = delete;

    Pokemon &operator=(const Pokemon &) = delete;

    Pokemon &operator=(Pokemon &&) noexcept = delete;

    ~Pokemon() override = default;

    [[nodiscard]] int numMoves() const;

    void addMove(const std::string &id);

    void deleteMove(int index);

    Project::Resource &getHp();

    [[nodiscard]] Project::Resource getHp() const;

    void initStatMods();

    void raiseStatMod(Stat stat, int amount);

    void lowerStatMod(Stat stat, int amount);

    [[nodiscard]] int getStatMod(Stat stat) const;

    [[nodiscard]] double getBaseStat(Stat stat) const;

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

    [[nodiscard]] bool isFasterThan(const Pokemon &pokemon) const;

    [[nodiscard]] bool rivalsInSpeed(const Pokemon &pokemon) const;

    [[nodiscard]] bool isAfflicted() const;

    [[nodiscard]] bool canAttack() const;

    [[nodiscard]] std::string hpEmptyMessage() const;

    [[nodiscard]] std::string hpFullMessage() const;

    Move &operator[](int index) const;

    std::vector<std::unique_ptr<Move>>::iterator begin();

    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator begin() const;

    std::vector<std::unique_ptr<Move>>::iterator end();

    [[nodiscard]] std::vector<std::unique_ptr<Move>>::const_iterator end() const;

private:
    Project::Resource hp{};

    std::array<int, 5> baseStats;
    std::array<int, 7> statModifiers;

    int level;

    std::vector<std::unique_ptr<Move>> moveSet;
    std::string ability;

    std::string gender;

    StatusCondition status{ StatusCondition::NONE };

    [[nodiscard]] double getStat(Stat stat) const;
};
