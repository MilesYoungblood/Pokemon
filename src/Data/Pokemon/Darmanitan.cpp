//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DARMANITAN, {
                "Darmanitan",
                "Blazing",
                Type::FIRE,
                Type::NONE,
                1.3,
                92.9,
                105,
                140,
                55,
                30,
                55,
                95,
                35,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
