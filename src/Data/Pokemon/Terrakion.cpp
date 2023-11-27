//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TERRAKION, {
                "Terrakion",
                "Cavern",
                Type::ROCK,
                Type::FIGHTING,
                1.9,
                260.0,
                91,
                129,
                90,
                72,
                90,
                108,
                42,
                3
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
