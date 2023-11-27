//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MIENSHAO, {
                "Mienshao",
                "Martial Arts",
                Type::FIGHTING,
                Type::NONE,
                1.4,
                35.5,
                65,
                125,
                60,
                95,
                60,
                105,
                50,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
