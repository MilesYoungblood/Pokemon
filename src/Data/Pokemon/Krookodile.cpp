//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KROOKODILE, {
                "Krookodile",
                "Intimidation",
                Type::GROUND,
                Type::DARK,
                1.5,
                96.3,
                95,
                117,
                80,
                65,
                70,
                92,
                40,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
