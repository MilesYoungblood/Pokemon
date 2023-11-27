//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GOLURK, {
                "Golurk",
                "Automaton",
                Type::GROUND,
                Type::GHOST,
                2.8,
                330.0,
                89,
                124,
                80,
                55,
                80,
                55,
                43,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
