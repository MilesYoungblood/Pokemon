//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VANILLITE, {
                "Vanillite",
                "Fresh Snow",
                Type::ICE,
                Type::NONE,
                0.4,
                5.7,
                36,
                50,
                50,
                65,
                60,
                44,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
