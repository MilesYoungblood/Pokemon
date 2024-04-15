//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../../../../../Enums/Time/Time.h"
#include "../../Item.h"

struct PokeBall : Item {
    explicit PokeBall(int n);

    PokeBall(int n, int x, int y);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] std::size_t getClass() const override;

    [[nodiscard]] virtual double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const;

    virtual void postCatch(Pokemon &pokemon) const;

    [[nodiscard]] std::string useMessage() const override;

    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const;

    [[nodiscard]] static std::vector<std::string> catchPokemonMessage(const Pokemon &pokemon,
                                                                       const std::array<bool, 4> &attempts);
};
