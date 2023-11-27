//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::AMOONGUSS, {
                "Amoonguss",
                "Mushroom",
                Type::GRASS,
                Type::POISON,
                0.6,
                10.5,
                114,
                85,
                70,
                85,
                80,
                30,
                39,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
