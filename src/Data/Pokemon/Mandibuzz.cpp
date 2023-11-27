//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::MANDIBUZZ, {
                "Mandibuzz",
                "Bone Vulture",
                Type::DARK,
                Type::FLYING,
                1.2,
                39.5,
                110,
                65,
                105,
                55,
                95,
                80,
                54,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
