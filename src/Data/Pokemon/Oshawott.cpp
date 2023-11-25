//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::OSHAWOTT, {
                "Oshawott",
                "Sea Otter",
                Type::WATER,
                Type::NONE,
                0.5,
                5.9,
                55,
                55,
                45,
                63,
                45,
                45,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke = (init(), true);
}
