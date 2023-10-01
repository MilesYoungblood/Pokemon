//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "../../Classes/Pokemon/Pokemon.h"

inline double checkNormal(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "ghost" or pokemon.getType(false) == "ghost")
        return 0.0;

    else if (pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel")
            return 0.25;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel")
            return 0.25;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFighting(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "ghost" or pokemon.getType(false) == "ghost")
        return 0.0;

    else if (pokemon.getType(true) == "normal" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "normal" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "steel")
            return 4.0;

        else if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "fairy") {
        if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "fairy")
            return 0.25;

        else if (pokemon.getType(false) == "normal" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "normal" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "normal" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "steel")
            return 4.0;

        else if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "fairy") {
        if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "fairy")
            return 0.25;

        else if (pokemon.getType(true) == "normal" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkPoison(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "steel" or pokemon.getType(false) == "steel")
        return 0.0;

    else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fairy") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fairy")
            return 4.0;

        else if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "ghost")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "ghost") {
        if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "ghost")
            return 0.25;

        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fairy")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fairy") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fairy")
            return 4.0;

        else if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "ghost")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "poison" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "ghost") {
        if (pokemon.getType(true) == "poison" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "ghost")
            return 0.25;

        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fairy")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkGround(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "flying" or pokemon.getType(false) == "flying")
        return 0.0;

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel")
            return 4.0;

        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "bug")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "bug") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "bug")
            return 0.25;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel")
            return 4.0;

        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "bug")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "bug") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "bug")
            return 0.25;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFlying(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "bug") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "bug")
            return 4.0;

        else if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "bug")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "bug") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "bug")
            return 4.0;

        else if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "bug")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkBug(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "dark") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "dark")
            return 4.0;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison" or
                 pokemon.getType(false) == "flying" or pokemon.getType(false) == "ghost" or pokemon.getType(false) == "steel" or
                 pokemon.getType(false) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison" or
             pokemon.getType(true) == "flying" or pokemon.getType(true) == "ghost" or pokemon.getType(true) == "steel" or
             pokemon.getType(true) == "fairy") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison" or
            pokemon.getType(false) == "flying" or pokemon.getType(false) == "ghost" or pokemon.getType(false) == "steel" or
            pokemon.getType(false) == "fairy")
            return 0.25;

        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "dark")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "psychic" or pokemon.getType(false) == "dark") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "dark")
            return 4.0;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison" or
                 pokemon.getType(true) == "flying" or pokemon.getType(true) == "ghost" or pokemon.getType(true) == "steel" or
                 pokemon.getType(true) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison" or
             pokemon.getType(false) == "flying" or pokemon.getType(false) == "ghost" or pokemon.getType(false) == "steel" or
             pokemon.getType(false) == "fairy") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison" or
            pokemon.getType(true) == "flying" or pokemon.getType(true) == "ghost" or pokemon.getType(true) == "steel" or
            pokemon.getType(true) == "fairy")
            return 0.25;

        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "psychic" or pokemon.getType(true) == "dark")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkRock(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "bug") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "bug")
            return 4.0;

        else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "bug")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "bug") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "bug")
            return 4.0;

        else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "bug")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkGhost(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "normal" or pokemon.getType(true) == "fighting" or pokemon.getType(false) == "normal" or pokemon.getType(false) == "fighting")
        return 0.0;

    else if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost") {
        if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost")
            return 4.0;

        else if (pokemon.getType(false) == "dark")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "dark") {
        if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost") {
        if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost")
            return 4.0;

        else if (pokemon.getType(true) == "dark")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "dark") {
        if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkSteel(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "fairy") {
        if (pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "fairy")
            return 4.0;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "fairy")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "ice" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "fairy") {
        if (pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "fairy")
            return 4.0;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "electric" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "electric" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "ice" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "fairy")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}