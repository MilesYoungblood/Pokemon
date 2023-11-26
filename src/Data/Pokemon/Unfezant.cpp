//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::UNFEZANT, {
                "Unfezant",
                "Proud",
                Type::NORMAL,
                Type::FLYING,
                1.2,
                29.0,
                80,
                115,
                80,
                65,
                55,
                93,
                32,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
