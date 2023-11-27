//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SWOOBAT, {
                "Swoobat",
                "Courting",
                Type::PSYCHIC,
                Type::FLYING,
                0.9,
                10.5,
                67,
                57,
                55,
                77,
                55,
                114,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
