//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::FOONGUS, {
                "Foongus",
                "Mushroom",
                Type::GRASS,
                Type::POISON,
                0.2,
                1.0,
                69,
                55,
                45,
                55,
                55,
                15,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
