//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GIGALITH, {
                "Gigalith",
                "Compressed",
                Type::ROCK,
                Type::NONE,
                1.7,
                260.0,
                85,
                135,
                130,
                60,
                80,
                25,
                25,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
