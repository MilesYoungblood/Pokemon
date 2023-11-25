//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SNIVY, {
                "Snivy",
                Type::GRASS,
                Type::NONE,
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

    [[maybe_unused]] bool invoke = (init(), true);
}
