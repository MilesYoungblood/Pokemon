//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move() {
    this->maxPp = 0;
    this->pp = 0;
    this->power = 0;
    this->accuracy = 0;
    this->type = "No type";
    this->category = "No category";
    this->name = "No name";
}

Move::Move(const char * name, const char * type, const char * category, int pp, int power, int accuracy) {
    this->maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    this->type = type;
    this->category = category;
    this->name = name;
}

Move::Move(const Move& moveToCopy) {
    this->pp = moveToCopy.pp;
    this->maxPp = moveToCopy.maxPp;
    this->power = moveToCopy.power;
    this->accuracy = moveToCopy.accuracy;
    this->type = moveToCopy.type;
    this->category = moveToCopy.category;
    this->name = moveToCopy.name;
}

Move& Move::operator=(const Move& rhs) {
    if (this != &rhs) {
        this->pp = rhs.pp;
        this->maxPp = rhs.maxPp;
        this->power = rhs.power;
        this->accuracy = rhs.accuracy;
        this->type = rhs.type;
        this->category = rhs.category;
        this->name = rhs.name;
    }

    return *this;
}

int Move::getDamage() {
    return generateInteger(1, 100) <= this->accuracy ? this->power : -1;
}

void Move::setPP(int newPP) {
    this->pp = newPP;
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

std::string Move::getType() const {
    return this->type;
}

std::string Move::getCategory() const {
    return this->category;
}

std::string Move::getName() const {
    return this->name;
}

bool Move::canUse() const {
    return this->pp > 0;
}

std::ostream& operator<<(std::ostream &out, const Move &move) {
    out << move.name;
    return out;
}