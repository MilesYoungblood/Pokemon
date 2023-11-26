//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ROGGENROLA, {
                "Roggenrola",
                "Mantle",
                Type::ROCK,
                Type::NONE,
                0.4,
                18.0,
                55,
                75,
                85,
                25,
                25,
                15,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
