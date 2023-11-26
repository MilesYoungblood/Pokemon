//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::STOUTLAND, {
                "Stoutland",
                "Big-Hearted",
                Type::NORMAL,
                Type::NONE,
                1.2,
                61.0,
                85,
                110,
                90,
                45,
                90,
                80,
                32,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
