//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::EMBOAR, {
                "Emboar",
                "Mega Fire Pig",
                Type::FIRE,
                Type::FIGHTING,
                1.6,
                150.0,
                110,
                123,
                65,
                100,
                65,
                65,
                36,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
