//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::FERROTHORN, {
                "Ferrothorn",
                "Thorn Pod",
                Type::GRASS,
                Type::STEEL,
                1.0,
                110.0,
                74,
                94,
                131,
                54,
                116,
                20,
                40,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
