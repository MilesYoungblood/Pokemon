//
// Created by Miles Youngblood on 10/5/2023.
//

#pragma once

#include "../../../Data/Pokedex.h"

struct PokemonFactory {
    static Pokemon* getPokemon(PokemonID id);
};
