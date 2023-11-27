//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::DEERLING, {
                "Deerling",
                "Season",
                Type::NORMAL,
                Type::GRASS,
                0.6,
                19.5,
                60,
                60,
                50,
                40,
                50,
                75,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
