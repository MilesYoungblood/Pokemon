//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SEISMITOAD, {
                "Seismitoad",
                "Vibration",
                Type::WATER,
                Type::GROUND,
                1.5,
                62.0,
                105,
                95,
                75,
                85,
                75,
                74,
                36,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
