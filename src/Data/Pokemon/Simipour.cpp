//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SIMIPOUR, {
                "Simipour",
                "Geyser",
                Type::WATER,
                Type::NONE,
                1.0,
                29.0,
                75,
                98,
                63,
                98,
                63,
                101,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
