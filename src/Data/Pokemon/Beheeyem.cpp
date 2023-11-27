//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BEHEEYEM, {
                "Beheeyem",
                "Cerebral",
                Type::PSYCHIC,
                Type::NONE,
                1.0,
                34.5,
                75,
                75,
                75,
                125,
                95,
                40,
                42,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
