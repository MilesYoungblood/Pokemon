//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VENIPEDE, {
                "Venipede",
                "Centipede",
                Type::BUG,
                Type::POISON,
                0.4,
                5.3,
                30,
                45,
                59,
                30,
                39,
                57,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
