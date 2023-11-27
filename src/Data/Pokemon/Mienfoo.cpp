//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MIENFOO, {
                "Mienfoo",
                "Martial Arts",
                Type::FIGHTING,
                Type::NONE,
                0.9,
                20.0,
                45,
                85,
                50,
                55,
                50,
                65,
                1,
                180
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
