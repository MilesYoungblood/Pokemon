//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CINCCINO, {
                "Cinccino",
                "Scarf",
                Type::NORMAL,
                Type::NONE,
                0.5,
                7.5,
                75,
                95,
                60,
                65,
                60,
                115,
                1,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
