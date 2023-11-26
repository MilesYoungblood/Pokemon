//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ZEBSTRIKA, {
                "Zebstrika",
                "Thunderbolt",
                Type::ELECTRIC,
                Type::NONE,
                1.6,
                79.5,
                75,
                100,
                63,
                80,
                63,
                116,
                27,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
