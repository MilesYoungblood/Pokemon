//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BLITZLE, {
                "Blitzle",
                "Electrified",
                Type::ELECTRIC,
                Type::NONE,
                0.8,
                29.8,
                45,
                60,
                32,
                50,
                32,
                76,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
