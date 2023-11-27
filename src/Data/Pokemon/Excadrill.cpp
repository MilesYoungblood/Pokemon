//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::EXCADRILL, {
                "Excadrill",
                "Subterrene",
                Type::GROUND,
                Type::STEEL,
                0.7,
                40.4,
                110,
                135,
                60,
                50,
                65,
                88,
                31,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
