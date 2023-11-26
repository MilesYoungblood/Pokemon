//
// Created by Miles on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::LIEPARD, {
                "Liepard",
                "Cruel",
                Type::DARK,
                Type::NONE,
                1.1,
                37.5,
                64,
                88,
                50,
                88,
                50,
                106,
                20,
                90
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
