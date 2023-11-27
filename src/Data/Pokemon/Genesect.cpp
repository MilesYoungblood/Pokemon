//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GENESECT, {
                "Genesect",
                "Paleozoic",
                Type::BUG,
                Type::STEEL,
                1.5,
                82.5,
                71,
                120,
                95,
                120,
                95,
                99,
                15,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
