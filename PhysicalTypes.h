//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "Pokemon.h"

double checkNormal(const Pokemon& pokemon) {
    if (pokemon.getType() == "ghost" or pokemon.getType(1) == "ghost") {
        return 0.0;
    }
    else if (pokemon.getType() == "rock" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
            return 0.25;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "rock" or pokemon.getType() == "steel") {
            return 0.25;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkFighting(const Pokemon& pokemon) {
    if (pokemon.getType() == "ghost" or pokemon.getType(1) == "ghost") {
        return 0.0;
    }
    else if (pokemon.getType() == "normal" or pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "dark" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "normal" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "steel") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "fairy") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "poison" or pokemon.getType() == "flying" or pokemon.getType() == "psychic" or pokemon.getType() == "bug" or pokemon.getType() == "fairy") {
        if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "fairy") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "normal" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "steel") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "normal" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "normal" or pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "dark" or pokemon.getType() == "steel") {
            return 4.0;
        }
        else if (pokemon.getType() == "poison" or pokemon.getType() == "flying" or pokemon.getType() == "psychic" or pokemon.getType() == "bug" or pokemon.getType() == "fairy") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "fairy") {
        if (pokemon.getType() == "poison" or pokemon.getType() == "flying" or pokemon.getType() == "psychic" or pokemon.getType() == "bug" or pokemon.getType() == "fairy") {
            return 0.25;
        }
        else if (pokemon.getType() == "normal" or pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "dark" or pokemon.getType() == "steel") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkPoison(const Pokemon& pokemon) {
    if (pokemon.getType() == "steel" or pokemon.getType(1) == "steel") {
        return 0.0;
    }
    else if (pokemon.getType() == "grass" or pokemon.getType() == "fairy") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fairy") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "ghost") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "poison" or pokemon.getType() == "ground" or pokemon.getType() == "rock" or pokemon.getType() == "ghost") {
        if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "ghost") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fairy") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fairy") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "fairy") {
            return 4.0;
        }
        else if (pokemon.getType() == "poison" or pokemon.getType() == "ground" or pokemon.getType() == "rock" or pokemon.getType() == "ghost") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "poison" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "ghost") {
        if (pokemon.getType() == "poison" or pokemon.getType() == "ground" or pokemon.getType() == "rock" or pokemon.getType() == "ghost") {
            return 0.25;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "fairy") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkGround(const Pokemon& pokemon) {
    if (pokemon.getType() == "flying" or pokemon.getType(1) == "flying") {
        return 0.0;
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "electric" or pokemon.getType() == "poison" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "bug") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "grass" or pokemon.getType() == "bug") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "bug") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "electric" or pokemon.getType() == "poison" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
            return 4.0;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "bug") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "bug") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "bug") {
            return 0.25;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "electric" or pokemon.getType() == "poison" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkFlying(const Pokemon& pokemon) {
    if (pokemon.getType() == "grass" or pokemon.getType() == "fighting" or pokemon.getType() == "bug") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "bug") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "electric" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "bug") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "bug") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "fighting" or pokemon.getType() == "bug") {
            return 4.0;
        }
        else if (pokemon.getType() == "electric" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "electric" or pokemon.getType() == "rock" or pokemon.getType() == "steel") {
            return 0.25;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "fighting" or pokemon.getType() == "bug") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkBug(const Pokemon& pokemon) {
    if (pokemon.getType() == "grass" or pokemon.getType() == "psychic" or pokemon.getType() == "dark") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "dark") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison" or
                 pokemon.getType(1) == "flying" or pokemon.getType(1) == "ghost" or pokemon.getType(1) == "steel" or
                 pokemon.getType(1) == "fairy") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "fighting" or pokemon.getType() == "poison" or
             pokemon.getType() == "flying" or pokemon.getType() == "ghost" or pokemon.getType() == "steel" or
             pokemon.getType() == "fairy") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison" or
            pokemon.getType(1) == "flying" or pokemon.getType(1) == "ghost" or pokemon.getType(1) == "steel" or
            pokemon.getType(1) == "fairy") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "dark") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "psychic" or pokemon.getType(1) == "dark") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "psychic" or pokemon.getType() == "dark") {
            return 4.0;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "fighting" or pokemon.getType() == "poison" or
                 pokemon.getType() == "flying" or pokemon.getType() == "ghost" or pokemon.getType() == "steel" or
                 pokemon.getType() == "fairy") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison" or
             pokemon.getType(1) == "flying" or pokemon.getType(1) == "ghost" or pokemon.getType(1) == "steel" or
             pokemon.getType(1) == "fairy") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "fighting" or pokemon.getType() == "poison" or
            pokemon.getType() == "flying" or pokemon.getType() == "ghost" or pokemon.getType() == "steel" or
            pokemon.getType() == "fairy") {
            return 0.25;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "psychic" or pokemon.getType() == "dark") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkRock(const Pokemon& pokemon) {
    if (pokemon.getType() == "fire" or pokemon.getType() == "ice" or pokemon.getType() == "flying" or pokemon.getType() == "bug") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "bug") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "fighting" or pokemon.getType() == "ground" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "steel") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "bug") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "bug") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "ice" or pokemon.getType() == "flying" or pokemon.getType() == "bug") {
            return 4.0;
        }
        else if (pokemon.getType() == "fighting" or pokemon.getType() == "ground" or pokemon.getType() == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fighting" or pokemon.getType() == "ground" or pokemon.getType() == "steel") {
            return 0.25;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "ice" or pokemon.getType() == "flying" or pokemon.getType() == "bug") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkGhost(const Pokemon& pokemon) {
    if (pokemon.getType() == "normal" or pokemon.getType() == "fighting" or pokemon.getType(1) == "normal" or pokemon.getType(1) == "fighting") {
        return 0.0;
    }
    else if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
        if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "dark") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "dark") {
        if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
        if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
            return 4.0;
        }
        else if (pokemon.getType() == "dark") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "dark") {
        if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}

double checkSteel(const Pokemon& pokemon) {
    if (pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "fairy") {
        if (pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "fairy") {
            return 4.0;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "electric" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "steel") {
            return 0.25;
        }
        else if (pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "fairy") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else if (pokemon.getType(1) == "ice" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "fairy") {
        if (pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "fairy") {
            return 4.0;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "electric" or pokemon.getType() == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "electric" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "electric" or pokemon.getType() == "steel") {
            return 0.25;
        }
        else if (pokemon.getType() == "ice" or pokemon.getType() == "rock" or pokemon.getType() == "fairy") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }
    else {
        return 1.0;
    }
}