//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "../../Item.h"

class PokeBall : public Item {
public:
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

    struct Data {
        std::string_view name;

        double (*catchRate)(const Pokemon &pokemon, Time time, int turn, bool isCave);

        void (*postCatch)(Pokemon &pokemon);
    };

    PokeBall(PokeBall::Id id, int n);

    static void init(PokeBall::Data (*instructions)(PokeBall::Id));

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const;

    void postCatch(Pokemon &pokemon) const;

    [[nodiscard]] PokeBall::Id getId() const;

    [[nodiscard]] Item::Class getClass() const override;

    void useMessage() override;

    bool catchPokemon(const Pokemon &pokemon, std::array<bool, 4> &attempts) const;

private:
    PokeBall::Id id;

    inline static PokeBall::Data (*dataFunction)(PokeBall::Id){ nullptr };
};
