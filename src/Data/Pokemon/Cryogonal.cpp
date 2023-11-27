//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CRYOGONAL, {
                "Cryogonal",
                "Crystallizing",
                Type::ICE,
                Type::NONE,
                1.1,
                148.0,
                80,
                50,
                50,
                95,
                135,
                105,
                1,
                25
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
