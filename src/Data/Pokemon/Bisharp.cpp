//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BISHARP, {
                "Bisharp",
                "Sword Blade",
                Type::DARK,
                Type::STEEL,
                1.6,
                70.0,
                65,
                125,
                100,
                60,
                70,
                70,
                52,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
