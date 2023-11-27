//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SWANNA, {
                "Swanna",
                "White Bird",
                Type::WATER,
                Type::FLYING,
                1.3,
                24.2,
                75,
                87,
                63,
                87,
                63,
                98,
                35,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
