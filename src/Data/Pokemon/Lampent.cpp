//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LAMPENT, {
                "Lampent",
                "Lamp",
                Type::GHOST,
                Type::FIRE,
                0.6,
                13.0,
                60,
                40,
                60,
                95,
                60,
                55,
                41,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
