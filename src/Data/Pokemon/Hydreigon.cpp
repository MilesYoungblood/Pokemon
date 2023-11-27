//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::HYDREIGON, {
                "Hydreigon",
                "Brutal",
                Type::DARK,
                Type::DRAGON,
                1.8,
                160.0,
                92,
                105,
                90,
                135,
                90,
                98,
                65,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
