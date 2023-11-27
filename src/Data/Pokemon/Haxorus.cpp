//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::HAXORUS, {
                "Haxorus",
                "Axe Jaw",
                Type::DRAGON,
                Type::NONE,
                1.8,
                105.5,
                76,
                147,
                90,
                60,
                70,
                97,
                48,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
