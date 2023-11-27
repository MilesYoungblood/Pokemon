//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ZOROARK, {
                "Zoroark",
                "Illusion Fox",
                Type::DARK,
                Type::NONE,
                1.6,
                81.1,
                60,
                105,
                60,
                120,
                60,
                105,
                30,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
