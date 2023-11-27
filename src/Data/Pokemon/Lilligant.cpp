//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LILLIGANT, {
                "Lilligant",
                "Flowering",
                Type::GRASS,
                Type::NONE,
                1.1,
                16.3,
                70,
                60,
                75,
                110,
                75,
                90,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
