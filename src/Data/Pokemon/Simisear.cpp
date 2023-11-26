//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SIMISEAR, {
                "Simisear",
                "Ember",
                Type::FIRE,
                Type::NONE,
                2.0,
                28.0,
                75,
                98,
                63,
                98,
                63,
                101,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
