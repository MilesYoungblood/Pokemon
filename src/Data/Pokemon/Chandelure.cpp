//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CHANDELURE, {
                "Chandelure",
                "Luring",
                Type::GHOST,
                Type::FIRE,
                1.0,
                34.3,
                60,
                55,
                90,
                145,
                90,
                80,
                41,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
