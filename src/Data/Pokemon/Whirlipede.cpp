//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::WHIRLIPEDE, {
                "Whirlipede",
                "Curlipede",
                Type::BUG,
                Type::POISON,
                1.2,
                58.5,
                40,
                55,
                99,
                40,
                79,
                47,
                22,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
