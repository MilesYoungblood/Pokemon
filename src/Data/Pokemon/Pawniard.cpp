//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PAWNIARD, {
                "Pawniard",
                "Sharp Blade",
                Type::DARK,
                Type::STEEL,
                0.5,
                10.2,
                45,
                85,
                70,
                40,
                40,
                60,
                1,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
