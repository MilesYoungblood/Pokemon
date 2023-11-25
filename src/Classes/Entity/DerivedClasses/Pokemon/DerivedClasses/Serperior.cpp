//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SERPERIOR, {
                "Serperior",
                Type::GRASS,
                Type::NONE,
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

    [[maybe_unused]] bool invoke = (init(), true);
}
