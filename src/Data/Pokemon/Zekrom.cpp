//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ZEKROM, {
                "Zekrom",
                "Deep Black",
                Type::DRAGON,
                Type::ELECTRIC,
                2.9,
                345.0,
                100,
                150,
                120,
                120,
                100,
                90,
                50,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
