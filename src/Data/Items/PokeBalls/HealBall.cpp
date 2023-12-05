//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::HEAL_BALL, {
                "Heal Ball",
                [](const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) -> double {
                    return 1.0;
                },
                [](Pokemon &pokemon) -> void {
                    pokemon.restoreHp(pokemon.getMaxHp() - pokemon.getHp());
                    pokemon.setStatus(StatusCondition::NONE);
                }
        }});
    }

    bool invoke{ (init(), true) };
}