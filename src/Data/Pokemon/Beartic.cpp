//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BEARTIC, {
                "Beartic",
                "Freezing",
                Type::ICE,
                Type::NONE,
                2.6,
                260.0,
                95,
                130,
                80,
                70,
                80,
                50,
                37,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
