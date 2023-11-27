//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LARVESTA, {
                "Larvesta",
                "Torch",
                Type::BUG,
                Type::FIRE,
                1.1,
                28.8,
                55,
                85,
                55,
                50,
                55,
                60,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
