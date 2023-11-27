//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DEINO, {
                "Deino",
                "Irate",
                Type::DARK,
                Type::DRAGON,
                0.8,
                17.3,
                52,
                65,
                50,
                45,
                50,
                38,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
