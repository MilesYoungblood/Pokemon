//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MELOETTA, {
                "Meloetta",
                "Melody",
                Type::NORMAL,
                Type::PSYCHIC,
                0.6,
                6.5,
                100,
                77,
                77,
                128,
                128,
                90,
                15,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
