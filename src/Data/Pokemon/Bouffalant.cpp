//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BOUFFALANT, {
                "Bouffalant",
                "Bash Buffalo",
                Type::NORMAL,
                Type::NONE,
                1.6,
                94.6,
                65,
                110,
                95,
                40,
                95,
                55,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
