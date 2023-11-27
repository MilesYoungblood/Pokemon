//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ARCHEOPS, {
                "Archeops",
                "First Bird",
                Type::ROCK,
                Type::FLYING,
                1.4,
                32.0,
                75,
                140,
                65,
                112,
                65,
                110,
                37,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
