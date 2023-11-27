//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GURDURR, {
                "Gurdurr",
                "Muscular",
                Type::FIGHTING,
                Type::NONE,
                1.2,
                40.0,
                85,
                105,
                85,
                40,
                50,
                40,
                25,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
