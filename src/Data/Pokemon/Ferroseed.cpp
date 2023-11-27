//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::FERROSEED, {
                "Ferroseed",
                "Thorn Seed",
                Type::GRASS,
                Type::STEEL,
                0.6,
                18.8,
                44,
                50,
                91,
                24,
                86,
                10,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
