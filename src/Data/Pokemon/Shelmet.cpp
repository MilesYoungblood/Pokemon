//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SHELMET, {
                "Shelmet",
                "Snail",
                Type::BUG,
                Type::NONE,
                0.4,
                7.7,
                50,
                40,
                85,
                40,
                65,
                25,
                1,
                200
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
