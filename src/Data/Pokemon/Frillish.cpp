//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::FRILLISH, {
                "Frillish",
                "Floating",
                Type::WATER,
                Type::GHOST,
                1.2,
                33.0,
                55,
                40,
                50,
                65,
                85,
                40,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
