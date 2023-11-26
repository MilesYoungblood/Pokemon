//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BOLDORE, {
                "Boldore",
                "Ore",
                Type::ROCK,
                Type::NONE,
                0.9,
                102.0,
                70,
                105,
                105,
                50,
                40,
                20,
                25,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
