//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::RUFFLET, {
                "Rufflet",
                "Eaglet",
                Type::NORMAL,
                Type::FLYING,
                0.5,
                10.5,
                70,
                83,
                50,
                37,
                50,
                60,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
