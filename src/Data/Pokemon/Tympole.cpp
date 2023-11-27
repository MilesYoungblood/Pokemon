//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TYMPOLE, {
                "Tympole",
                "Tadpole",
                Type::WATER,
                Type::NONE,
                0.5,
                4.5,
                50,
                50,
                40,
                50,
                40,
                64,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
