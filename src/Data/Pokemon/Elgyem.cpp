//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ELGYEM, {
                "Elgyem",
                "Cerebral",
                Type::PSYCHIC,
                Type::NONE,
                0.5,
                9.0,
                55,
                55,
                55,
                85,
                55,
                30,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
