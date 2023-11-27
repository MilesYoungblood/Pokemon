//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::EELEKTRIK, {
                "Eelektrik",
                "EleFish",
                Type::ELECTRIC,
                Type::NONE,
                1.2,
                22.0,
                65,
                85,
                70,
                75,
                70,
                40,
                39,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
