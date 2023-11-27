//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::AUDINO, {
                "Audino",
                "Hearing",
                Type::NORMAL,
                Type::NONE,
                1.1,
                31.0,
                103,
                60,
                86,
                60,
                86,
                50,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
