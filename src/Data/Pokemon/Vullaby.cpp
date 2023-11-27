//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::VULLABY, {
                "Vullaby",
                "Diapered",
                Type::DARK,
                Type::FLYING,
                0.5,
                9.0,
                70,
                55,
                75,
                45,
                65,
                60,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
