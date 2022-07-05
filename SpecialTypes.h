//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "Pokemon.h"

float checkFire(const Pokemon& pokemon) {
    if (pokemon.getType() == "grass" or pokemon.getType() == "ice" or pokemon.getType() == "bug" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "steel") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "rock" or pokemon.getType() == "dragon") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "ice" or pokemon.getType() == "bug" or pokemon.getType() == "steel") {
            return 4.0f;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "rock" or pokemon.getType() == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "rock" or pokemon.getType(1) == "dragon") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "rock" or pokemon.getType() == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "ice" or pokemon.getType() == "bug" or pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkWater(const Pokemon& pokemon) {
    if (pokemon.getType() == "fire" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "water" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
        if (pokemon.getType(1) == "water" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
            return 4.0f;
        }
        else if (pokemon.getType() == "water" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
        if (pokemon.getType() == "water" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkElectric(const Pokemon& pokemon) {
    if (pokemon.getType() == "ground" or pokemon.getType(1) == "ground") {
        return 0.0f;
    }
    else if (pokemon.getType() == "water" or pokemon.getType() == "flying") {
        if (pokemon.getType(1) == "water" or pokemon.getType(1) == "flying") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "electric" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
        if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "flying") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "flying") {
        if (pokemon.getType() == "water" or pokemon.getType() == "flying") {
            return 4.0f;
        }
        else if (pokemon.getType() == "electric" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "electric" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "dragon") {
        if (pokemon.getType() == "electric" or pokemon.getType() == "grass" or pokemon.getType() == "dragon") {
            return 0.25f;
        }
        else if (pokemon.getType() == "water" or pokemon.getType() == "flying") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkGrass(const Pokemon& pokemon) {
    if (pokemon.getType() == "water" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
        if (pokemon.getType(1) == "water" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "poison" or
                 pokemon.getType(1) == "flying" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "grass" or pokemon.getType() == "poison" or pokemon.getType() == "flying" or
             pokemon.getType() == "bug" or pokemon.getType() == "dragon" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "poison" or
            pokemon.getType(1) == "flying" or pokemon.getType(1) == "bug" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "water" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "rock") {
        if (pokemon.getType() == "water" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
            return 4.0f;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "grass" or pokemon.getType() == "poison" or
                 pokemon.getType() == "flying" or pokemon.getType() == "bug" or pokemon.getType() == "dragon" or pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "grass" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "flying" or
             pokemon.getType(1) == "bug" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "grass" or pokemon.getType() == "poison" or
            pokemon.getType() == "flying" or pokemon.getType() == "bug" or pokemon.getType() == "dragon" or pokemon.getType() == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType() == "water" or pokemon.getType() == "ground" or pokemon.getType() == "rock") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkIce(const Pokemon& pokemon) {
    if (pokemon.getType() == "grass" or pokemon.getType() == "ground" or pokemon.getType() == "flying" or pokemon.getType() == "dragon") {
        if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "dragon") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "ice" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "dragon") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "grass" or pokemon.getType(1) == "ground" or pokemon.getType(1) == "flying" or pokemon.getType(1) == "dragon") {
        if (pokemon.getType() == "grass" or pokemon.getType() == "ground" or pokemon.getType() == "flying" or pokemon.getType() == "dragon") {
            return 4.0f;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "ice" or pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "water" or pokemon.getType(1) == "ice" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "water" or pokemon.getType() == "ice" or pokemon.getType() == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType() == "grass" or pokemon.getType() == "ground" or pokemon.getType() == "flying" or pokemon.getType() == "dragon") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkPsychic(const Pokemon& pokemon) {
    if (pokemon.getType() == "dark" or pokemon.getType(1) == "dark") {
        return 0.0f;
    }
    else if (pokemon.getType() == "fighting" or pokemon.getType() == "poison") {
        if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "psychic" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "poison") {
        if (pokemon.getType() == "fighting" or pokemon.getType() == "poison") {
            return 4.0f;
        }
        else if (pokemon.getType() == "psychic" or pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "psychic" or pokemon.getType() == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType() == "fighting" or pokemon.getType() == "poison") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkDragon(const Pokemon& pokemon) {
    if (pokemon.getType() == "fairy" or pokemon.getType(1) == "fairy") {
        return 0.0f;
    }
    else if (pokemon.getType() == "dragon") {
        if (pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "dragon") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "dragon") {
        if (pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "dragon") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkDark(const Pokemon& pokemon) {
    if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
        if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "fairy") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "fighting" or pokemon.getType() == "dark" or pokemon.getType() == "fairy") {
        if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "fairy") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "psychic" or pokemon.getType(1) == "ghost") {
        if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
            return 4.0f;
        }
        else if (pokemon.getType() == "fighting" or pokemon.getType() == "dark" or pokemon.getType() == "fairy") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dark" or pokemon.getType(1) == "fairy") {
        if (pokemon.getType() == "fighting" or pokemon.getType() == "dark" or pokemon.getType() == "fairy") {
            return 0.25f;
        }
        else if (pokemon.getType() == "psychic" or pokemon.getType() == "ghost") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}

float checkFairy(const Pokemon& pokemon) {
    if (pokemon.getType() == "fighting" or pokemon.getType() == "dragon" or pokemon.getType() == "dark") {
        if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "dark") {
            return 4.0f;
        }
        else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType() == "fire" or pokemon.getType() == "poison" or pokemon.getType() == "steel") {
        if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "dark") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else if (pokemon.getType(1) == "fighting" or pokemon.getType(1) == "dragon" or pokemon.getType(1) == "dark") {
        if (pokemon.getType() == "fighting" or pokemon.getType() == "dragon" or pokemon.getType() == "dark") {
            return 4.0f;
        }
        else if (pokemon.getType() == "fire" or pokemon.getType() == "poison" or pokemon.getType() == "steel") {
            return 1.0f;
        }
        else {
            return 2.0f;
        }
    }
    else if (pokemon.getType(1) == "fire" or pokemon.getType(1) == "poison" or pokemon.getType(1) == "steel") {
        if (pokemon.getType() == "fire" or pokemon.getType() == "poison" or pokemon.getType() == "steel") {
            return 0.25f;
        }
        else if (pokemon.getType() == "fighting" or pokemon.getType() == "dragon" or pokemon.getType() == "dark") {
            return 1.0f;
        }
        else {
            return 0.5f;
        }
    }
    else {
        return 1.0f;
    }
}