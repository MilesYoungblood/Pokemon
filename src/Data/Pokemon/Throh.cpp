//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::THROH, {
                "Throh",
                "Judo",
                Type::FIGHTING,
                Type::NONE,
                1.3,
                55.5,
                120,
                100,
                85,
                30,
                85,
                45,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
