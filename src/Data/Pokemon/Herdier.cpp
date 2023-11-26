//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::HERDIER, {
                "Herdier",
                "Loyal Dog",
                Type::NORMAL,
                Type::NONE,
                0.9,
                14.7,
                65,
                80,
                65,
                35,
                65,
                60,
                16,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
