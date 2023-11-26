//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PATRAT, {
                "Patrat",
                "Scout",
                Type::NORMAL,
                Type::NONE,
                0.5,
                11.6,
                45,
                55,
                39,
                35,
                39,
                42,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
