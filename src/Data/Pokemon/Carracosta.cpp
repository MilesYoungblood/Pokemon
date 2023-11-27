//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::CARRACOSTA, {
                "Carracosta",
                "Prototurtle",
                Type::WATER,
                Type::ROCK,
                1.2,
                81.0,
                74,
                108,
                133,
                83,
                65,
                32,
                37,
                45
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
