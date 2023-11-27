//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::HEATMOR, {
                "Heatmor",
                "Anteater",
                Type::FIRE,
                Type::NONE,
                1.4,
                58.0,
                85,
                97,
                66,
                105,
                66,
                65,
                1,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
