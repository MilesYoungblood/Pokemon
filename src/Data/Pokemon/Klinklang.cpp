//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KLINKLANG, {
                "Klinklang",
                "Gear",
                Type::STEEL,
                Type::NONE,
                0.6,
                81.0,
                60,
                100,
                115,
                70,
                85,
                90,
                49,
                30
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
