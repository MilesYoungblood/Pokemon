//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::KELDEO, {
                "Keldeo",
                "Colt",
                Type::WATER,
                Type::FIGHTING,
                1.4,
                48.5,
                91,
                72,
                90,
                129,
                90,
                108,
                15,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
