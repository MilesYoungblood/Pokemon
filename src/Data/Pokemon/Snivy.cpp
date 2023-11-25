//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SNIVY, {
                "Snivy",
                "Grass Snake",
                Type::GRASS,
                Type::NONE,
                0.6,
                8.1,
                45,
                45,
                55,
                45,
                55,
                63,
                1,
                45
        }});
    }

    [[maybe_unused]] [[maybe_unused]] bool invoke = (init(), true);
}
