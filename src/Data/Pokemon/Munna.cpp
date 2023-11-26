//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MUNNA, {
                "Munna",
                "Dream Eater",
                Type::PSYCHIC,
                Type::NONE,
                0.6,
                23.3,
                76,
                25,
                45,
                67,
                55,
                24,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
