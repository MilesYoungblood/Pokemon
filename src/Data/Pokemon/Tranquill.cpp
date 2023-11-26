//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TRANQUILL, {
                "Tranquill",
                "Wild Pigeon",
                Type::NORMAL,
                Type::FLYING,
                0.6,
                15.0,
                62,
                77,
                62,
                50,
                42,
                65,
                21,
                120
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
