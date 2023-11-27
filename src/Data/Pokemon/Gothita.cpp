//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GOTHITA, {
                "Gothita",
                "Fixation",
                Type::PSYCHIC,
                Type::NONE,
                0.4,
                5.8,
                45,
                30,
                50,
                55,
                65,
                45,
                1,
                200
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
