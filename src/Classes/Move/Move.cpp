//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move(const char *name, const int pp, const int power, const int accuracy, const Type type, const Category category) {
    this->name = name;
    this->maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    this->type = type;
    this->category = category;
}

int Move::getDamage() const {
    return generateInteger(1, 100) <= this->accuracy ? this->power : -1;
}

void Move::setPP(const int newPP) {
    this->pp = newPP;

    // PP cannot be set lower than 0
    if (this->pp < 0) {
        this->pp = 0;
    }
    // PP cannot be set higher than max PP
    else if (this->pp > this->maxPp) {
        this->pp = this->maxPp;
    }
}
int Move::getPP() const {
    return this->pp;
}

int Move::getMaxPP() const {
    return this->maxPp;
}

int Move::getPower() const {
    return this->power;
}

int Move::getAccuracy() const {
    return this->accuracy;
}

Type Move::getType() const {
    return this->type;
}

const char *Move::getTypeAsString() const {
    switch (this->type) {
        case Type::NORMAL:
            return "normal";

        case Type::FIRE:
            return "fire";

        case Type::WATER:
            return "water";

        case Type::ELECTRIC:
            return "electric";

        case Type::GRASS:
            return "grass";

        case Type::ICE:
            return "ice";

        case Type::FIGHTING:
            return "fighting";

        case Type::POISON:
            return "poison";

        case Type::GROUND:
            return "ground";

        case Type::FLYING:
            return "flying";

        case Type::PSYCHIC:
            return "psychic";

        case Type::BUG:
            return "bug";

        case Type::ROCK:
            return "rock";

        case Type::GHOST:
            return "ghost";

        case Type::DRAGON:
            return "dragon";

        case Type::DARK:
            return "dark";

        case Type::STEEL:
            return "steel";

        case Type::FAIRY:
            return "fairy";

        default:
            throw std::runtime_error("Unexpected error: function getTypeAsString");
    }
}

Category Move::getCategory() const {
    return this->category;
}

const char *Move::getCategoryAsString() const {
    switch (this->category) {
        case Category::PHYSICAL:
            return "physical";

        case Category::SPECIAL:
            return "special";

        case Category::STATUS:
            return "status";

        default:
            throw std::runtime_error("Unexpected error: function getCategoryAsString");
    }
}

std::string Move::getName() const {
    return this->name;
}

Move::operator bool() const {
    return this->pp > 0;
}

std::ostream& operator<<(std::ostream &out, const Move &move) {
    out << move.name;
    return out;
}
