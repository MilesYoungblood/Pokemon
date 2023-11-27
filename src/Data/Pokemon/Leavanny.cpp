//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LEAVANNY, {
                "Leavanny",
                "Nurturing",
                Type::BUG,
                Type::GRASS,
                1.2,
                20.5,
                75,
                103,
                80,
                70,
                80,
                92,
                20,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
