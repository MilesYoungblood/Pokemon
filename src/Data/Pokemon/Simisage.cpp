//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SIMISAGE, {
                "Simisage",
                "Thorn Monkey",
                Type::GRASS,
                Type::NONE,
                1.1,
                30.5,
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
