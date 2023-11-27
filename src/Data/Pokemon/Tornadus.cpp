//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TORNADUS, {
                "Tornadus",
                "Cyclone",
                Type::FLYING,
                Type::NONE,
                1.5,
                63.0,
                79,
                115,
                70,
                125,
                80,
                111,
                40,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
