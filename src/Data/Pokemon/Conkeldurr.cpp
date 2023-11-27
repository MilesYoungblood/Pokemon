//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CONKELDURR, {
                "Conkeldurr",
                "Muscular",
                Type::FIGHTING,
                Type::NONE,
                1.4,
                87.0,
                105,
                140,
                95,
                55,
                65,
                45,
                25,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
