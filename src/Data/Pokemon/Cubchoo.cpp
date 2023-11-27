//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CUBCHOO, {
                "Cubchoo",
                "Chill",
                Type::ICE,
                Type::NONE,
                0.5,
                8.5,
                55,
                70,
                40,
                60,
                40,
                40,
                1,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
