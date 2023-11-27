//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CRUSTLE, {
                "Crustle",
                "Stone Home",
                Type::BUG,
                Type::ROCK,
                1.4,
                200.0,
                70,
                105,
                125,
                65,
                75,
                45,
                34,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
