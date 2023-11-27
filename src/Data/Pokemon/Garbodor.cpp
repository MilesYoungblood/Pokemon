//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GARBODOR, {
                "Garbodor",
                "Trash Heap",
                Type::POISON,
                Type::NONE,
                1.9,
                107.3,
                80,
                95,
                82,
                60,
                82,
                75,
                36,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
