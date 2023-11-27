//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DURANT, {
                "Durant",
                "Iron Ant",
                Type::BUG,
                Type::STEEL,
                0.3,
                33.0,
                58,
                109,
                112,
                48,
                48,
                109,
                1,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
