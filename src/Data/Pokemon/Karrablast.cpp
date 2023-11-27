//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KARRABLAST, {
                "Karrablast",
                "Clamping",
                Type::BUG,
                Type::NONE,
                0.5,
                5.9,
                50,
                75,
                45,
                40,
                45,
                60,
                1,
                200
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
