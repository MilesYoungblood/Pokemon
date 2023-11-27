//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LANDORUS, {
                "Landorus",
                "Abundance",
                Type::GROUND,
                Type::FLYING,
                1.5,
                68.0,
                89,
                125,
                90,
                115,
                80,
                101,
                70,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
