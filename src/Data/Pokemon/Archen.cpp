//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ARCHEN, {
                "Archen",
                "First Bird",
                Type::ROCK,
                Type::FLYING,
                0.5,
                9.5,
                55,
                112,
                45,
                74,
                45,
                70,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
