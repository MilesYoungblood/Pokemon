//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::BASCULIN, {
                "Basculin",
                "Hostile",
                Type::WATER,
                Type::NONE,
                1.0,
                18.0,
                70,
                92,
                65,
                80,
                55,
                98,
                1,
                25
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
