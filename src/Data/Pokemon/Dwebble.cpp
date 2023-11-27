//
// Created by Miles Youngblood on 11/26/2023.
//


#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DWEBBLE, {
                "Dwebble",
                "Rock Inn",
                Type::BUG,
                Type::ROCK,
                0.3,
                14.5,
                50,
                65,
                85,
                35,
                35,
                55,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
