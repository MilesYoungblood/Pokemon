//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VIRIZION, {
                "Virizion",
                "Grassland",
                Type::GRASS,
                Type::FIGHTING,
                2.0,
                200.0,
                91,
                90,
                72,
                90,
                129,
                108,
                42,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
