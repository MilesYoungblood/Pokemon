//
// Created by Miles Youngblood on 11/26/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::JELLICENT, {
                "Jellicent",
                "Floating",
                Type::WATER,
                Type::GHOST,
                2.2,
                135.0,
                100,
                60,
                70,
                85,
                105,
                60,
                40,
                60
        }});
    }

    [[maybe_unused]] bool invoke{ (init(), true) };
}
