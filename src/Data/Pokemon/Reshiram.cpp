//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::RESHIRAM, {
                "Reshiram",
                "Vast White",
                Type::DRAGON,
                Type::FIRE,
                3.2,
                330.0,
                100,
                120,
                100,
                150,
                120,
                90,
                50,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
