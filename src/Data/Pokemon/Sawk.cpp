//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SAWK, {
                "Sawk",
                "Karate",
                Type::FIGHTING,
                Type::NONE,
                1.4,
                51.0,
                75,
                125,
                75,
                30,
                75,
                85,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
