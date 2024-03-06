//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "../../Singleton.h"

class Pokedex : public Singleton<Pokedex> {
private:
    enum : Uint8 {
        NUM_POKEMON = 156
    };
    template<typename T>
    using set = std::array<T, NUM_POKEMON>;

    set<std::string> names;
    set<std::string> species;
    set<Type> type1Array{};
    set<Type> type2Array{};
    set<Ability::Id> ability1Array{};
    set<Ability::Id> ability2Array{};
    set<double> heights{};
    set<double> weights{};
    set<double> genderRatios{};
    set<std::array<int, 6>> baseStats{};
    set<int> catchRates{};

public:
    Pokedex();

    Pokedex(const Pokedex &) = default;

    Pokedex(Pokedex &&) noexcept = default;

    Pokedex &operator=(const Pokedex &) = default;

    Pokedex &operator=(Pokedex &&) noexcept = default;

    ~Pokedex() override = default;
};
