//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LITWICK, {
                "Litwick",
                "Candle",
                Type::GHOST,
                Type::FIRE,
                0.3,
                3.1,
                50,
                30,
                55,
                65,
                55,
                20,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
