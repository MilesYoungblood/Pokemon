//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SANDILE, {
                "Sandile",
                "Desert Croc",
                Type::GROUND,
                Type::DARK,
                0.7,
                15.2,
                50,
                72,
                35,
                35,
                35,
                65,
                1,
                180
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
