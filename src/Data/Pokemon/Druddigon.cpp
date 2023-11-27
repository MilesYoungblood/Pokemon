//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DRUDDIGON, {
                "Druddigon",
                "Cave",
                Type::DRAGON,
                Type::NONE,
                1.6,
                139.0,
                77,
                120,
                90,
                60,
                90,
                48,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
