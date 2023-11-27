//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::REUNICLUS, {
                "Reuniclus",
                "Multiplying",
                Type::PSYCHIC,
                Type::NONE,
                1.0,
                20.1,
                110,
                65,
                75,
                125,
                85,
                30,
                41,
                50
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
