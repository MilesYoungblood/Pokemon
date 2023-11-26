//
// Created by Miles Youngblood on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::PIGNITE, {
                "Pignite",
                "Fire Pig",
                Type::FIRE,
                Type::FIGHTING,
                1.0,
                55.5,
                90,
                93,
                55,
                70,
                55,
                55,
                17,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
