//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DARUMAKA, {
                "Darumaka",
                "Zen Charm",
                Type::FIRE,
                Type::NONE,
                0.6,
                37.5,
                70,
                90,
                45,
                15,
                45,
                50,
                1,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
