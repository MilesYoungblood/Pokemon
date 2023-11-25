//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::WATCHOG, {
                "Watchog",
                "Lookout",
                Type::NORMAL,
                Type::NONE,
                1.1,
                27.0,
                60,
                85,
                69,
                60,
                69,
                77,
                20,
                255
        }});
    }

    [[maybe_unused]] bool invoke = (init(), true);
}
