//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move(const char * name, Type type, Category category, int pp, int power, int accuracy) {
    this->maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    this->type = type;
    this->category = category;
    this->name = name;
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

Type Move::getType() const {
    return this->type;
}

Category Move::getCategory() const {
    return this->category;
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