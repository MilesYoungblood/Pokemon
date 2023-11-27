//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::AXEW, {
                "Axew",
                "Tusk",
                Type::DRAGON,
                Type::NONE,
                0.6,
                18.0,
                46,
                87,
                60,
                30,
                40,
                57,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
