//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GOTHORITA, {
                "Gothorita",
                "Manipulate",
                Type::PSYCHIC,
                Type::NONE,
                0.7,
                18.0,
                60,
                45,
                70,
                75,
                85,
                55,
                32,
                100
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
