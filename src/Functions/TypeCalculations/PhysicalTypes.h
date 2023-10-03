//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "../../Classes/Pokemon/Pokemon.h"

inline double checkNormal(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GHOST or pokemon.getType(false) == Type::GHOST)
        return 0.0;

    else if (pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFighting(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GHOST or pokemon.getType(false) == Type::GHOST)
        return 0.0;

    else if (pokemon.getType(true) == Type::NORMAL or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::NORMAL or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::FAIRY) {
        if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(false) == Type::NORMAL or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::NORMAL or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::NORMAL or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::FAIRY) {
        if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(true) == Type::NORMAL or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkPoison(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::STEEL or pokemon.getType(false) == Type::STEEL)
        return 0.0;

    else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FAIRY) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FAIRY)
            return 4.0;

        else if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::GHOST)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::GHOST) {
        if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::GHOST)
            return 0.25;

        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FAIRY)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FAIRY) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FAIRY)
            return 4.0;

        else if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::GHOST)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::GHOST) {
        if (pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::GHOST)
            return 0.25;

        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FAIRY)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkGround(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::FLYING or pokemon.getType(false) == Type::FLYING)
        return 0.0;

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::BUG)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::BUG) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::BUG)
            return 0.25;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::BUG)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::BUG) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::BUG)
            return 0.25;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFlying(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::BUG) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::BUG)
            return 4.0;

        else if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::BUG)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::BUG) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::BUG)
            return 4.0;

        else if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::BUG)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkBug(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::DARK) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::DARK)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON or
                 pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::GHOST or pokemon.getType(false) == Type::STEEL or
                 pokemon.getType(false) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON or
             pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::GHOST or pokemon.getType(true) == Type::STEEL or
             pokemon.getType(true) == Type::FAIRY) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON or
            pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::GHOST or pokemon.getType(false) == Type::STEEL or
            pokemon.getType(false) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::DARK)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::DARK) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::DARK)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON or
                 pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::GHOST or pokemon.getType(true) == Type::STEEL or
                 pokemon.getType(true) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON or
             pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::GHOST or pokemon.getType(false) == Type::STEEL or
             pokemon.getType(false) == Type::FAIRY) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON or
            pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::GHOST or pokemon.getType(true) == Type::STEEL or
            pokemon.getType(true) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::DARK)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkRock(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::BUG) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::BUG)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::BUG)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::BUG) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::BUG)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::BUG)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkGhost(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::NORMAL or pokemon.getType(true) == Type::FIGHTING or pokemon.getType(false) == Type::NORMAL or pokemon.getType(false) == Type::FIGHTING)
        return 0.0;

    else if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST) {
        if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST)
            return 4.0;

        else if (pokemon.getType(false) == Type::DARK)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::DARK) {
        if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST) {
        if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST)
            return 4.0;

        else if (pokemon.getType(true) == Type::DARK)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::DARK) {
        if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkSteel(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::FAIRY) {
        if (pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::FAIRY)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::FAIRY)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::FAIRY) {
        if (pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::FAIRY)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::FAIRY)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}