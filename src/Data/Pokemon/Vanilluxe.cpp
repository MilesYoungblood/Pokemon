//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VANILLUXE, {
                "Vanilluxe",
                "Snowstorm",
                Type::ICE,
                Type::NONE,
                1.3,
                57.5,
                71,
                95,
                85,
                110,
                95,
                79,
                47,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
