//
// Created by Miles on 11/24/2023.
//

#include "Pokedex.h"

namespace {
    void init() {
        pokemonLookupTable[Pokemon::Id::VICTINI].name = "Victini";
        pokemonLookupTable[Pokemon::Id::VICTINI].type1 = Type::PSYCHIC;
        pokemonLookupTable[Pokemon::Id::VICTINI].type2 = Type::FIRE;
        pokemonLookupTable[Pokemon::Id::VICTINI].catchRate = 3;
    }

    [[maybe_unused]] int invoke = (init(), 0);
}
