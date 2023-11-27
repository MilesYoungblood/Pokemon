//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::COFAGRIGUS, {
                "Cofagrigus",
                "Coffin",
                Type::GHOST,
                Type::NONE,
                1.7,
                76.5,
                58,
                50,
                145,
                95,
                105,
                30,
                34,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
