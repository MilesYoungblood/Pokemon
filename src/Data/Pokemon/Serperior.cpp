//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SERPERIOR, {
                "Serperior",
                "Regal",
                Type::GRASS,
                Type::NONE,
                3.3,
                63.0,
                75,
                75,
                95,
                75,
                95,
                113,
                36,
                45
        }});
    }

    [[maybe_unused]] [[maybe_unused]] bool invoke = (init(), true);
}
