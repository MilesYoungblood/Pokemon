//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

struct PokeBall : public Item {
    enum class Id {
        POKE_BALL,
        GREAT_BALL,
        ULTRA_BALL,
        MASTER_BALL,
        NET_BALL,
        NEST_BALL,
        TIMER_BALL,
        PREMIER_BALL,
        DUSK_BALL,
        HEAL_BALL,
        QUICK_BALL
    };

    explicit PokeBall(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] virtual double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const;

    virtual void postCatch(Pokemon &pokemon) const;

    [[nodiscard]] virtual PokeBall::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

    [[nodiscard]] std::string useMessage() const override;

    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const;
};

inline std::mutex pokeBallMutex;
inline std::unordered_map<PokeBall::Id, std::unique_ptr<PokeBall>(*)(int)> pokeBalls;