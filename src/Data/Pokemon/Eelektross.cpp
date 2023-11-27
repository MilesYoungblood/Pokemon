//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::EELEKTROSS, {
                "Eelektross",
                "EleFish",
                Type::ELECTRIC,
                Type::NONE,
                2.1,
                80.5,
                85,
                115,
                80,
                105,
                80,
                50,
                39,
                30
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
