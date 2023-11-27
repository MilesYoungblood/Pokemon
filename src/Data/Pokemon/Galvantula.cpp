//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GALVANTULA, {
                "Galvantula",
                "EleSpider",
                Type::BUG,
                Type::ELECTRIC,
                0.8,
                14.3,
                70,
                77,
                60,
                97,
                60,
                108,
                36,
                75
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
