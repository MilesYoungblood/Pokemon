//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../../../../../Enums/Time/Time.h"
#include "../../Item.h"

struct PokeBall : public Item {
    explicit PokeBall(int n);

    PokeBall(int n, int x, int y);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] virtual double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const;

    virtual void postCatch(Pokemon &pokemon) const;

    [[nodiscard]] Item::Class getClass() const override;

    [[nodiscard]] std::string useMessage() const override;

    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const;
};

inline std::mutex pokeBallMutex;
inline std::unordered_map<std::string, std::unique_ptr<PokeBall>(*)(int)> pokeBalls;
