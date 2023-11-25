//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LILLIPUP, {
                "Lillipup",
                "Puppy",
                Type::NORMAL,
                Type::NONE,
                0.4,
                4.1,
                45,
                60,
                45,
                25,
                45,
                55,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke = (init(), true);
}