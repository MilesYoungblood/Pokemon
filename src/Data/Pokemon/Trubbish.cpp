//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TRUBBISH, {
                "Trubbish",
                "Trash Bag",
                Type::POISON,
                Type::NONE,
                0.6,
                31.0,
                50,
                50,
                62,
                40,
                62,
                65,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
