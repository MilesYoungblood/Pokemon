//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DUCKLETT, {
                "Ducklett",
                "Water Bird",
                Type::WATER,
                Type::FLYING,
                0.5,
                5.5,
                62,
                44,
                50,
                44,
                50,
                55,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
