//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SCRAFTY, {
                "Scrafty",
                "Hoodlum",
                Type::DARK,
                Type::FIGHTING,
                1.1,
                30.0,
                65,
                90,
                115,
                45,
                115,
                58,
                39,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
