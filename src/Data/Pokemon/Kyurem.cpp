//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KYUREM, {
                "Kyurem",
                "Boundary",
                Type::DRAGON,
                Type::ICE,
                3.0,
                325.0,
                125,
                130,
                90,
                130,
                90,
                95,
                75,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
