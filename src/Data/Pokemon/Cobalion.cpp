//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::COBALION, {
                "Cobalion",
                "Iron Will",
                Type::STEEL,
                Type::FIGHTING,
                2.1,
                250.0,
                91,
                90,
                129,
                90,
                72,
                108,
                42,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
