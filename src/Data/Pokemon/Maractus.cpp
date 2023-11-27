//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MARACTUS, {
                "Maractus",
                "Cactus",
                Type::GRASS,
                Type::NONE,
                1.0,
                28.0,
                75,
                86,
                67,
                106,
                67,
                60,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
