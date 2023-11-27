//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::GOLETT, {
                "Golett",
                "Automaton",
                Type::GROUND,
                Type::GHOST,
                1.0,
                92.0,
                59,
                74,
                50,
                35,
                50,
                35,
                1,
                190
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
