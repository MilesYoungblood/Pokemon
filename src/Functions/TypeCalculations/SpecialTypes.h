//
// Created by Miles Youngblood on 6/10/2022.
//

#pragma once

#include "../../Classes/Pokemon/Pokemon.h"

inline double checkFire(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DRAGON) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::STEEL)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ROCK or pokemon.getType(false) == Type::DRAGON) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ROCK or pokemon.getType(true) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkWater(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK)
            return 4.0;

        else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON) {
        if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK)
            return 4.0;

        else if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON) {
        if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkElectric(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GROUND or pokemon.getType(false) == Type::GROUND)
        return 0.0;

    else if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::FLYING) {
        if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::FLYING)
            return 4.0;

        else if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON) {
        if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::FLYING)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::FLYING) {
        if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::FLYING)
            return 4.0;

        else if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON)
            return 1.0;

        else
            return 2.0;

    }

    else if (pokemon.getType(false) == Type::ELECTRIC or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::DRAGON) {
        if (pokemon.getType(true) == Type::ELECTRIC or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::DRAGON)
            return 0.25;

        else if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::FLYING)
            return 1.0;

        else
            return 0.5;

    }

    else
        return 1.0;
}

inline double checkGrass(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK) {
        if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::POISON or
                 pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::FLYING or
             pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::POISON or
            pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::ROCK) {
        if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::POISON or
                 pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::FLYING or
             pokemon.getType(false) == Type::BUG or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::POISON or
            pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::BUG or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::ROCK)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkIce(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::DRAGON) {
        if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::DRAGON) {
            return 4.0;
        }
        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::STEEL) {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::STEEL) {
            return 0.25;
        }
        else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::DRAGON) {
            return 1.0;
        }
        else {
            return 0.5;
        }
    }

    else if (pokemon.getType(false) == Type::GRASS or pokemon.getType(false) == Type::GROUND or pokemon.getType(false) == Type::FLYING or pokemon.getType(false) == Type::DRAGON) {
        if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::DRAGON) {
            return 4.0;
        }
        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::STEEL) {
            return 1.0;
        }
        else {
            return 2.0;
        }
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::ICE or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::ICE or pokemon.getType(true) == Type::STEEL) {
            return 0.25;
        }
        else if (pokemon.getType(true) == Type::GRASS or pokemon.getType(true) == Type::GROUND or pokemon.getType(true) == Type::FLYING or pokemon.getType(true) == Type::DRAGON) {
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
    if (pokemon.getType(true) == Type::DARK or pokemon.getType(false) == Type::DARK)
        return 0.0;

    else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON) {
        if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON)
            return 4.0;

        else if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::POISON) {
        if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON)
            return 4.0;

        else if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::POISON)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkDragon(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::FAIRY or pokemon.getType(false) == Type::FAIRY)
        return 0.0;

    else if (pokemon.getType(true) == Type::DRAGON) {
        if (pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::DRAGON)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::DRAGON) {
        if (pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::DRAGON)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkDark(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST) {
        if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::FAIRY) {
        if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::PSYCHIC or pokemon.getType(false) == Type::GHOST) {
        if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::FAIRY)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DARK or pokemon.getType(false) == Type::FAIRY) {
        if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DARK or pokemon.getType(true) == Type::FAIRY)
            return 0.25;

        else if (pokemon.getType(true) == Type::PSYCHIC or pokemon.getType(true) == Type::GHOST)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}

inline double checkFairy(const Pokemon& pokemon) {
    if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::DARK) {
        if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::DARK)
            return 4.0;

        else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::STEEL) {
        if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::DARK)
            return 1.0;

        else
            return 0.5;
    }

    else if (pokemon.getType(false) == Type::FIGHTING or pokemon.getType(false) == Type::DRAGON or pokemon.getType(false) == Type::DARK) {
        if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::DARK)
            return 4.0;

        else if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::STEEL)
            return 1.0;

        else
            return 2.0;
    }

    else if (pokemon.getType(false) == Type::FIRE or pokemon.getType(false) == Type::POISON or pokemon.getType(false) == Type::STEEL) {
        if (pokemon.getType(true) == Type::FIRE or pokemon.getType(true) == Type::POISON or pokemon.getType(true) == Type::STEEL)
            return 0.25;

        else if (pokemon.getType(true) == Type::FIGHTING or pokemon.getType(true) == Type::DRAGON or pokemon.getType(true) == Type::DARK)
            return 1.0;

        else
            return 0.5;
    }

    else
        return 1.0;
}