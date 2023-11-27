//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DRILBUR, {
                "Drilbur",
                "Mole",
                Type::GROUND,
                Type::NONE,
                0.3,
                8.5,
                60,
                85,
                40,
                30,
                45,
                68,
                1,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
