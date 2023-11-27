//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ACCELGOR, {
                "Accelgor",
                "Shell Out",
                Type::BUG,
                Type::NONE,
                0.8,
                25.3,
                80,
                70,
                40,
                100,
                60,
                145,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
