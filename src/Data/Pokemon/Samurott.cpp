//
// Created by Miles Youngblood on 11/25/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable.insert({ Pokemon::Id::SAMUROTT, {
                "Samurott",
                "Formidable",
                Type::WATER,
                Type::NONE,
                1.5,
                94.6,
                95,
                100,
                85,
                108,
                70,
                70,
                36,
                45
        }});
    }

    [[maybe_unused]] bool invoke = (init(), true);
}
