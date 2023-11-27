//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::WOOBAT, {
                "Woobat",
                "Bat",
                Type::PSYCHIC,
                Type::FLYING,
                0.4,
                2.1,
                65,
                45,
                43,
                55,
                43,
                72,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
