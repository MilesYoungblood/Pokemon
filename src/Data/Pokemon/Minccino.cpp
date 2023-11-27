//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MINCCINO, {
                "Minccino",
                "Chinchilla",
                Type::NORMAL,
                Type::NONE,
                0.4,
                5.8,
                55,
                50,
                40,
                40,
                40,
                75,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
