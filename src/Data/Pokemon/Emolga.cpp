//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::EMOLGA, {
                "Emolga",
                "Sky Squirrel",
                Type::ELECTRIC,
                Type::FLYING,
                0.4,
                5.0,
                55,
                75,
                60,
                75,
                60,
                103,
                1,
                200
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
