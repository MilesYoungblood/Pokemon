//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::JOLTIK, {
                "Joltik",
                "Attaching",
                Type::BUG,
                Type::ELECTRIC,
                0.1,
                0.6,
                50,
                47,
                50,
                57,
                50,
                65,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
