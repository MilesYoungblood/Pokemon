//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::WHIMSICOTT, {
                "Whimsicott",
                "Windveiled",
                Type::GRASS,
                Type::NONE,
                0.7,
                6.6,
                60,
                67,
                85,
                77,
                75,
                116,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
