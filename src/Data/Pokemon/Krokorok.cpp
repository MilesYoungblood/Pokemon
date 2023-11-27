//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KROKOROK, {
                "Krokorok",
                "Desert Croc",
                Type::GROUND,
                Type::DARK,
                1.0,
                33.4,
                60,
                82,
                45,
                45,
                45,
                74,
                29,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
