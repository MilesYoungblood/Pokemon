//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SCRAGGY, {
                "Scraggy",
                "Shedding",
                Type::DARK,
                Type::FIGHTING,
                0.6,
                11.8,
                50,
                75,
                70,
                35,
                70,
                48,
                1,
                180
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
