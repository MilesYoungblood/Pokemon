//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TEPIG, {
                "Tepig",
                "Fire Pig",
                Type::FIRE,
                Type::NONE,
                0.5,
                9.9,
                65,
                63,
                45,
                45,
                45,
                45,
                1,
                45
        }});
    }

    [[maybe_unused]] [[maybe_unused]] bool invoke = (init(), true);
}
