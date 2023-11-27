//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KLINK, {
                "Klink",
                "Gear",
                Type::STEEL,
                Type::NONE,
                0.3,
                21.0,
                40,
                55,
                70,
                45,
                60,
                30,
                1,
                130
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
