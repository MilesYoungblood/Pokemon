//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TEPIG, {
                "Tepig",
                Type::FIRE,
                Type::NONE,
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

    [[maybe_unused]] bool invoke = (init(), true);
}
