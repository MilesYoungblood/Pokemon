//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DEWOTT, {
                "Dewott",
                "Discipline",
                Type::WATER,
                Type::NONE,
                0.8,
                24.5,
                75,
                75,
                60,
                83,
                60,
                60,
                17,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
