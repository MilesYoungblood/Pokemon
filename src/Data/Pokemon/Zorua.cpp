//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ZORUA, {
                "Zorua",
                "Tricky Fox",
                Type::DARK,
                Type::NONE,
                0.7,
                12.5,
                40,
                65,
                40,
                80,
                40,
                65,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
