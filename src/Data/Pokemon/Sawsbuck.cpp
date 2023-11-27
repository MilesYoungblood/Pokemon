//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SAWSBUCK, {
                "Sawsbuck",
                "Season",
                Type::NORMAL,
                Type::GRASS,
                1.9,
                92.5,
                80,
                100,
                70,
                60,
                70,
                95,
                34,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
