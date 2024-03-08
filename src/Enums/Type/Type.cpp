//
// Created by Miles Youngblood on 3/7/2024.
//

#include "Type.h"

const char *typeToString(Type type) {
    switch (type) {
        case Type::NONE:
            return "N/A";
        case Type::NORMAL:
            return "Normal";
        case Type::FIRE:
            return "Fire";
        case Type::WATER:
            return "Water";
        case Type::ELECTRIC:
            return "Electric";
        case Type::GRASS:
            return "Grass";
        case Type::ICE:
            return "Ice";
        case Type::FIGHTING:
            return "Fighting";
        case Type::POISON:
            return "Poison";
        case Type::GROUND:
            return "Ground";
        case Type::FLYING:
            return "Flying";
        case Type::PSYCHIC:
            return "Psychic";
        case Type::BUG:
            return "Bug";
        case Type::ROCK:
            return "Rock";
        case Type::GHOST:
            return "Ghost";
        case Type::DRAGON:
            return "Dragon";
        case Type::DARK:
            return "Dark";
        case Type::STEEL:
            return "Steel";
        default:
            throw std::runtime_error("Unexpected error: function typeToColor\n");
    }
}

SDL_Color typeToColor(Type type) {
    switch (type) {
        case Type::NONE:
            return Constants::Color::WHITE;
        case Type::NORMAL:
            return Constants::Color::LIGHT_GRAY;
        case Type::FIRE:
            return Constants::Color::RED;
        case Type::WATER:
            return Constants::Color::BLUE;
        case Type::ELECTRIC:
            return Constants::Color::YELLOW;
        case Type::GRASS:
            return Constants::Color::GREEN;
        case Type::ICE:
            return Constants::Color::CYAN;
        case Type::FIGHTING:
            return Constants::Color::BROWN;
        case Type::POISON:
            return Constants::Color::PURPLE;
        case Type::GROUND:
            return Constants::Color::BRONZE;
        case Type::FLYING:
            return Constants::Color::SKY_BLUE;
        case Type::PSYCHIC:
            return Constants::Color::HOT_PINK;
        case Type::BUG:
            return Constants::Color::YELLOW_GREEN;
        case Type::ROCK:
            return Constants::Color::SAND;
        case Type::GHOST:
            return Constants::Color::INDIGO;
        case Type::DRAGON:
            return Constants::Color::ROYAL_BLUE;
        case Type::DARK:
            return Constants::Color::DARK_BROWN;
        case Type::STEEL:
            return Constants::Color::PLATINUM;
        default:
            throw std::runtime_error("Unexpected error: function typeToColor\n");
    }
}
