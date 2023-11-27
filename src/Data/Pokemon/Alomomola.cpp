//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::ALOMOMOLA, {
                "Alomomola",
                "Caring",
                Type::WATER,
                Type::NONE,
                1.2,
                31.6,
                165,
                75,
                80,
                40,
                45,
                65,
                1,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
