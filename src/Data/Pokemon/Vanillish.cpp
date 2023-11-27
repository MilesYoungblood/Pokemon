//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VANILLISH, {
                "Vanillish",
                "Icy Snow",
                Type::ICE,
                Type::NONE,
                1.1,
                41.0,
                51,
                65,
                65,
                80,
                75,
                59,
                35,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
