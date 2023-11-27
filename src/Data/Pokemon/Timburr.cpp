//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TIMBURR, {
                "Timburr",
                "Muscular",
                Type::FIGHTING,
                Type::NONE,
                0.6,
                12.5,
                75,
                80,
                55,
                25,
                35,
                35,
                1,
                180
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
