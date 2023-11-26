//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PIDOVE, {
                "Pidove",
                "Tiny Pigeon",
                Type::NORMAL,
                Type::FLYING,
                0.3,
                2.1,
                50,
                55,
                50,
                36,
                30,
                43,
                1,
                255
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
