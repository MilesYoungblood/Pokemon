//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::STUNFISK, {
                "Stunfisk",
                "Trap",
                Type::GROUND,
                Type::ELECTRIC,
                0.7,
                11.0,
                109,
                66,
                84,
                81,
                99,
                32,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
