//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PURRLOIN, {
                "Purrloin",
                "Devious",
                Type::DARK,
                Type::NONE,
                0.4,
                10.1,
                41,
                50,
                37,
                50,
                37,
                66,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
