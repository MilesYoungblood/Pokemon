//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PANSAGE, {
                "Pansage",
                "Grass Monkey",
                Type::GRASS,
                Type::NONE,
                0.6,
                10.5,
                50,
                53,
                48,
                53,
                48,
                64,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
