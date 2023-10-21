//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "PhysicalTypes.h"
#include "SpecialTypes.h"

inline auto getTypeEffective(const Move &move, const Pokemon &pokemon) -> double {
    switch (move.getType()) {
        case Type::NORMAL:
            return checkNormal(pokemon);
        case Type::FIRE:
            return checkFire(pokemon);
        case Type::WATER:
            return checkWater(pokemon);
        case Type::ELECTRIC:
            return checkElectric(pokemon);
        case Type::GRASS:
            return checkGrass(pokemon);
        case Type::ICE:
            return checkIce(pokemon);
        case Type::FIGHTING:
            return checkFighting(pokemon);
        case Type::POISON:
            return checkPoison(pokemon);
        case Type::GROUND:
            return checkGround(pokemon);
        case Type::FLYING:
            return checkFlying(pokemon);
        case Type::PSYCHIC:
            return checkPsychic(pokemon);
        case Type::BUG:
            return checkBug(pokemon);
        case Type::ROCK:
            return checkRock(pokemon);
        case Type::GHOST:
            return checkGhost(pokemon);
        case Type::DRAGON:
            return checkDragon(pokemon);
        case Type::DARK:
            return checkDark(pokemon);
        case Type::STEEL:
            return checkSteel(pokemon);
        case Type::FAIRY:
            return checkFairy(pokemon);
        default:
            throw std::runtime_error("Unexpected error: function getTypeEffective");
    }
}
