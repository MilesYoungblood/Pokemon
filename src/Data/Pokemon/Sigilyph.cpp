//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SIGILYPH, {
                "Sigilyph",
                "Avianoid",
                Type::PSYCHIC,
                Type::FLYING,
                1.4,
                14.0,
                72,
                58,
                80,
                103,
                80,
                97,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
