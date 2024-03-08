//
// Created by Miles Youngblood on 3/7/2024.
//

#pragma once

enum class Type : Uint8 {
    NONE, NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON,
    DARK, STEEL
};

const char *typeToString(Type type);

SDL_Color typeToColor(Type type);
