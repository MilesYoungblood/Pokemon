//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PALPITOAD, {
                "Palpitoad",
                "Vibration",
                Type::WATER,
                Type::GROUND,
                0.8,
                17.0,
                75,
                65,
                55,
                65,
                55,
                69,
                25,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
