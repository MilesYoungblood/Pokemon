//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SEWADDLE, {
                "Sewaddle",
                "Sewing",
                Type::BUG,
                Type::GRASS,
                0.3,
                2.5,
                45,
                53,
                70,
                40,
                60,
                42,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
