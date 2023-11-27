//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ESCAVALIER, {
                "Escavalier",
                "Cavalry",
                Type::BUG,
                Type::STEEL,
                1.0,
                33.0,
                70,
                135,
                105,
                60,
                105,
                20,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
