//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PETILIL, {
                "Petilil",
                "Bulb",
                Type::GRASS,
                Type::NONE,
                0.5,
                6.6,
                45,
                35,
                50,
                70,
                50,
                30,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
