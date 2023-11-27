//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ZWEILOUS, {
                "Zweilous",
                "Hostile",
                Type::DARK,
                Type::DRAGON,
                1.4,
                50.0,
                72,
                85,
                70,
                65,
                70,
                58,
                50,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
