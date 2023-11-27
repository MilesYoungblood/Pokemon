//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DUOSION, {
                "Duosion",
                "Mitosis",
                Type::PSYCHIC,
                Type::NONE,
                0.6,
                8.0,
                65,
                40,
                50,
                125,
                60,
                30,
                32,
                100
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
