//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MUSHARNA, {
                "Musharna",
                "Drowsing",
                Type::PSYCHIC,
                Type::NONE,
                1.1,
                60.5,
                116,
                55,
                85,
                107,
                95,
                29,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
