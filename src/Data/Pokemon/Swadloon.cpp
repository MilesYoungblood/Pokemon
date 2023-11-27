//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SWADLOON, {
                "Swadloon",
                "Leaf-Wrapped",
                Type::BUG,
                Type::GRASS,
                0.5,
                7.3,
                55,
                63,
                90,
                50,
                80,
                42,
                20,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
