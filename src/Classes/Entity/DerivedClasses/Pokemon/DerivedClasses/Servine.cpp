//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SERVINE, {
                "Servine",
                Type::GRASS,
                Type::NONE,
                60,
                60,
                75,
                60,
                75,
                83,
                17,
                45
        }});
    }

    [[maybe_unused]] bool invoke = (init(), true);
}
