//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "PhysicalTypes.h"
#include "SpecialTypes.h"

double getTypeEffective(const Moves& move, const Pokemon& pokemon) {
    double multiplier = 1.0;

    if (move.getType() == "normal") {
        multiplier = checkNormal(pokemon);
    }
    else if (move.getType() == "fire") {
        multiplier = checkFire(pokemon);
    }
    else if (move.getType() == "water") {
        multiplier = checkWater(pokemon);
    }
    else if (move.getType() == "electric") {
        multiplier = checkElectric(pokemon);
    }
    else if (move.getType() == "grass") {
        multiplier = checkGrass(pokemon);
    }
    else if (move.getType() == "ice") {
        multiplier = checkIce(pokemon);
    }
    else if (move.getType() == "fighting") {
        multiplier = checkFighting(pokemon);
    }
    else if (move.getType() == "poison") {
        multiplier = checkPoison(pokemon);
    }
    else if (move.getType() == "ground") {
        multiplier = checkGround(pokemon);
    }
    else if (move.getType() == "flying") {
        multiplier = checkFlying(pokemon);
    }
    else if (move.getType() == "psychic") {
        multiplier = checkPsychic(pokemon);
    }
    else if (move.getType() == "bug") {
        multiplier = checkBug(pokemon);
    }
    else if (move.getType() == "rock") {
        multiplier = checkRock(pokemon);
    }
    else if (move.getType() == "ghost") {
        multiplier = checkGhost(pokemon);
    }
    else if (move.getType() == "dragon") {
        multiplier = checkDragon(pokemon);
    }
    else if (move.getType() == "dark") {
        multiplier = checkDark(pokemon);
    }
    else if (move.getType() == "steel") {
        multiplier = checkSteel(pokemon);
    }
    else if (move.getType() == "fairy") {
        multiplier = checkFairy(pokemon);
    }

    return multiplier;
}