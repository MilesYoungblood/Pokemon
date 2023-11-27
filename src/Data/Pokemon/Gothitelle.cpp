//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GOTHITELLE, {
                "Gothitelle",
                "Astral Body",
                Type::PSYCHIC,
                Type::NONE,
                1.5,
                44.0,
                70,
                55,
                95,
                95,
                110,
                65,
                41,
                50
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
