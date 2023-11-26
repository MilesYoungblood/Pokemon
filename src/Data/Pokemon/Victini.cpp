//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VICTINI, {
                "Victini",
                "Victory",
                Type::PSYCHIC,
                Type::FIRE,
                0.4,
                4.0,
                100,
                100,
                100,
                100,
                100,
                100,
                15,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
