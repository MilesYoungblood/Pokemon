//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::COTTONEE, {
                "Cottonee",
                "Cotton Puff",
                Type::GRASS,
                Type::NONE,
                0.3,
                0.6,
                40,
                27,
                60,
                37,
                50,
                66,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
