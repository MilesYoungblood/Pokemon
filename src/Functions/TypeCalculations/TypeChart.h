//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "PhysicalTypes.h"
#include "SpecialTypes.h"

inline double getTypeEffective(const Move& move, const Pokemon& pokemon) {
    if (move.getType() == "normal")
        return checkNormal(pokemon);

    else if (move.getType() == "fire")
        return checkFire(pokemon);

    else if (move.getType() == "water")
        return checkWater(pokemon);

    else if (move.getType() == "electric")
        return checkElectric(pokemon);

    else if (move.getType() == "grass")
        return checkGrass(pokemon);

    else if (move.getType() == "ice")
        return checkIce(pokemon);

    else if (move.getType() == "fighting")
        return checkFighting(pokemon);

    else if (move.getType() == "poison")
        return checkPoison(pokemon);

    else if (move.getType() == "ground")
        return checkGround(pokemon);

    else if (move.getType() == "flying")
        return checkFlying(pokemon);

    else if (move.getType() == "psychic")
        return checkPsychic(pokemon);

    else if (move.getType() == "bug")
        return checkBug(pokemon);

    else if (move.getType() == "rock")
        return checkRock(pokemon);

    else if (move.getType() == "ghost")
        return checkGhost(pokemon);

    else if (move.getType() == "dragon")
        return checkDragon(pokemon);

    else if (move.getType() == "dark")
        return checkDark(pokemon);

    else if (move.getType() == "steel")
        return checkSteel(pokemon);

    else if (move.getType() == "fairy")
        return checkFairy(pokemon);

    else
        return 1.0;
}