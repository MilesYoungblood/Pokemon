//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::TIRTOUGA, {
                "Tirtouga",
                "Prototurtle",
                Type::WATER,
                Type::ROCK,
                0.7,
                16.5,
                54,
                78,
                103,
                53,
                45,
                22,
                1,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
