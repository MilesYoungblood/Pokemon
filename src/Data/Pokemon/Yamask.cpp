//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::YAMASK, {
                "Yamask",
                "Spirit",
                Type::GHOST,
                Type::NONE,
                0.5,
                1.5,
                38,
                30,
                85,
                55,
                65,
                30,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
