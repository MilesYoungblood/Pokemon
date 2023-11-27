//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SOLOSIS, {
                "Solosis",
                "Cell",
                Type::PSYCHIC,
                Type::NONE,
                0.3,
                1.0,
                45,
                30,
                40,
                105,
                50,
                20,
                1,
                200
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
