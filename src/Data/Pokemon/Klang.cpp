//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KLANG, {
                "Klang",
                "Gear",
                Type::STEEL,
                Type::NONE,
                0.6,
                51.0,
                60,
                80,
                95,
                70,
                85,
                50,
                38,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
