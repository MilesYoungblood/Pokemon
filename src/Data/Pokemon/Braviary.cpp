//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BRAVIARY, {
                "Braviary",
                "Valiant",
                Type::NORMAL,
                Type::FLYING,
                1.5,
                41.0,
                100,
                123,
                75,
                57,
                75,
                80,
                54,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
