//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TYNAMO, {
                "Tynamo",
                "EleFish",
                Type::ELECTRIC,
                Type::NONE,
                0.2,
                0.3,
                35,
                55,
                40,
                45,
                40,
                60,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
