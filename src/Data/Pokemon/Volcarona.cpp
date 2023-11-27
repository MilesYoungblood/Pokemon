//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VOLCARONA, {
                "Volcarona",
                "Sun",
                Type::BUG,
                Type::FIRE,
                1.6,
                46.0,
                85,
                60,
                65,
                135,
                105,
                100,
                59,
                15
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
