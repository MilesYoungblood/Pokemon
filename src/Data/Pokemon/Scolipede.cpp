//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SCOLIPEDE, {
                "Scolipede",
                "Megapede",
                Type::BUG,
                Type::POISON,
                2.5,
                200.5,
                60,
                100,
                89,
                55,
                69,
                112,
                30,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
