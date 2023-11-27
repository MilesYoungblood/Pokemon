//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::FRAXURE, {
                "Fraxure",
                "Axe Jaw",
                Type::DRAGON,
                Type::NONE,
                1.0,
                36.0,
                66,
                117,
                70,
                40,
                50,
                67,
                38,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
