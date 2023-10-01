//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "../../Classes/Pokemon/Pokemon.h"

inline double checkFire(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "steel")
            return 4.0;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dragon")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dragon") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dragon")
            return 0.25;

        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "steel")
            return 4.0;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dragon")
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "rock" or pokemon.getType(false) == "dragon") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "rock" or pokemon.getType(true) == "dragon")
            return 0.25;

        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkWater(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock")
            return 4.0;

        else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "water" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon") {
        if (pokemon.getType(false) == "water" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon")
            return 0.25;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock")
            return 4.0;

        else if (pokemon.getType(true) == "water" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon")
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon") {
        if (pokemon.getType(true) == "water" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon")
            return 0.25;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkElectric(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "ground" or pokemon.getType(false) == "ground")
        return 0.0;

    else if (pokemon.getType(true) == "water" or pokemon.getType(true) == "flying") {
        if (pokemon.getType(false) == "water" or pokemon.getType(false) == "flying")
            return 4.0;

        else if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon")
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon") {
        if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon")
            return 0.25;

        else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "flying")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "flying") {
        if (pokemon.getType(true) == "water" or pokemon.getType(true) == "flying")
            return 4.0;

        else if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon")
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == "electric" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "dragon") {
        if (pokemon.getType(true) == "electric" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "dragon")
            return 0.25;

        else if (pokemon.getType(true) == "water" or pokemon.getType(true) == "flying")
            return 1.0;

        else
            return 0.5;

    }

    else
        return 1.0;
}

inline double checkGrass(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "water" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock") {
        if (pokemon.getType(false) == "water" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock")
            return 4.0;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "poison" or
                 pokemon.getType(false) == "flying" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "flying" or
             pokemon.getType(true) == "bug" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "poison" or
            pokemon.getType(false) == "flying" or pokemon.getType(false) == "bug" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "water" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "rock") {
        if (pokemon.getType(true) == "water" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock")
            return 4.0;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "poison" or
                 pokemon.getType(true) == "flying" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "grass" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "flying" or
             pokemon.getType(false) == "bug" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "grass" or pokemon.getType(true) == "poison" or
            pokemon.getType(true) == "flying" or pokemon.getType(true) == "bug" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "water" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "rock")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkIce(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "dragon") {
        if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "dragon") {
            return 4.0;
        }
        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "steel") {
            return 0.25;
        }
        else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "dragon") {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }

    else if (pokemon.getType(false) == "grass" or pokemon.getType(false) == "ground" or pokemon.getType(false) == "flying" or pokemon.getType(false) == "dragon") {
        if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "dragon") {
            return 4.0;
        }
        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "steel") {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "water" or pokemon.getType(false) == "ice" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "water" or pokemon.getType(true) == "ice" or pokemon.getType(true) == "steel") {
            return 0.25;
        }
        else if (pokemon.getType(true) == "grass" or pokemon.getType(true) == "ground" or pokemon.getType(true) == "flying" or pokemon.getType(true) == "dragon") {
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

inline double checkPsychic(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "dark" or pokemon.getType(false) == "dark")
        return 0.0;

    else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison") {
        if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison")
            return 4.0;

        else if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "poison") {
        if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison")
            return 4.0;

        else if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "poison")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkDragon(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "fairy" or pokemon.getType(false) == "fairy")
        return 0.0;

    else if (pokemon.getType(true) == "dragon") {
        if (pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "dragon")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "dragon") {
        if (pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "dragon")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkDark(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost") {
        if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost")
            return 4.0;

        else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "fairy") {
        if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "fairy")
            return 0.25;

        else if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "psychic" or pokemon.getType(false) == "ghost") {
        if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost")
            return 4.0;

        else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "fairy")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dark" or pokemon.getType(false) == "fairy") {
        if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dark" or pokemon.getType(true) == "fairy")
            return 0.25;

        else if (pokemon.getType(true) == "psychic" or pokemon.getType(true) == "ghost")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFairy(const Pokemon& pokemon) {
    if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "dark") {
        if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "dark")
            return 4.0;

        else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "steel") {
        if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "steel")
            return 0.25;

        else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "dark")
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == "fighting" or pokemon.getType(false) == "dragon" or pokemon.getType(false) == "dark") {
        if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "dark")
            return 4.0;

        else if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "steel")
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == "fire" or pokemon.getType(false) == "poison" or pokemon.getType(false) == "steel") {
        if (pokemon.getType(true) == "fire" or pokemon.getType(true) == "poison" or pokemon.getType(true) == "steel")
            return 0.25;

        else if (pokemon.getType(true) == "fighting" or pokemon.getType(true) == "dragon" or pokemon.getType(true) == "dark")
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}