//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "../../Singleton.h"

class Pokedex : public Singleton<Pokedex> {
private:
    enum : Uint8 {
        NUM_POKEMON = 156
    };
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

public:
    Pokedex();

    Pokedex(const Pokedex &) = default;

    Pokedex(Pokedex &&) noexcept = default;

    Pokedex &operator=(const Pokedex &) = default;

    Pokedex &operator=(Pokedex &&) noexcept = default;

    ~Pokedex() override = default;

    std::string getSpecies(const std::string &id) const;

    Type getType1(const std::string &id) const;

    Type getType2(const std::string &id) const;

    double getHeight(const std::string &id) const;

    double getWeight(const std::string &id) const;

    double getGenderRatio(const std::string &id) const;

    int getBaseStat(const std::string &id, int stat) const;

    int getBaseLevel(const std::string &id) const;

    int getCatchRate(const std::string &id) const;

    int getDexNum(const std::string &id) const;
};
