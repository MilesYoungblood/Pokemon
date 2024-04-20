//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "../Singleton.h"

class Pokedex final : public Singleton<Pokedex> {
public:
    Pokedex();

    Pokedex(const Pokedex &) = default;

    Pokedex(Pokedex &&) noexcept = default;

    Pokedex &operator=(const Pokedex &) = default;

    Pokedex &operator=(Pokedex &&) noexcept = default;

    ~Pokedex() override = default;

    [[nodiscard]] std::string getSpecies(const std::string &id) const;

    [[nodiscard]] Type getType1(const std::string &id) const;

    [[nodiscard]] Type getType2(const std::string &id) const;

    [[nodiscard]] double getHeight(const std::string &id) const;

    [[nodiscard]] double getWeight(const std::string &id) const;

    [[nodiscard]] double getGenderRatio(const std::string &id) const;

    [[nodiscard]] int getBaseStat(const std::string &id, int stat) const;

    [[nodiscard]] int getBaseLevel(const std::string &id) const;

    [[nodiscard]] int getCatchRate(const std::string &id) const;

    [[nodiscard]] int getDexNum(const std::string &id) const;

private:
    template<typename T>
    using set = std::unordered_map<std::string, T>;

    set<std::string> species;
    set<Type> type1Array{};
    set<Type> type2Array{};
    set<std::string> ability1Array{};
    set<std::string> ability2Array{};
    set<double> heights{};
    set<double> weights{};
    set<double> genderRatios{};
    set<std::array<int, 6>> baseStats{};
    set<int> baseLevels{};
    set<int> catchRates{};
    set<int> dexNums{};
};
