//
// Created by miles on 5/5/2022.
//

#include "Moves.h"

Moves::Moves() {
    maxPp = 0;
    pp = 0;
    power = 0;
    accuracy = 0;
    type = "No type";
    category = "No category";
    name = "No name";
}

Moves::Moves(const std::string& name, const std::string& type, const std::string& category, int pp, int power, int accuracy) {
    maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    this->type = type;
    this->category = category;
    this->name = name;
}

Moves::Moves(const Moves& moveToCopy) {
    pp = moveToCopy.pp;
    maxPp = moveToCopy.maxPp;
    power = moveToCopy.power;
    accuracy = moveToCopy.accuracy;
    type = moveToCopy.type;
    category = moveToCopy.category;
    name = moveToCopy.name;
}

int Moves::getDamage() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    return dist(mt) <= accuracy ? power : -1;
}

void Moves::setPP(int newPP) {
    pp = newPP;
}
int Moves::getPP() const {
    return pp;
}

int Moves::getMaxPP() const {
    return maxPp;
}

int Moves::getPower() const {
    return power;
}

int Moves::getAccuracy() const {
    return accuracy;
}

__attribute__((unused)) void Moves::setType(std::string& newType) {
    type = newType;
}
__attribute__((unused)) std::string Moves::getType() const {
    return type;
}

std::string Moves::getCategory() const {
    return category;
}

std::string Moves::getName() const {
    return name;
}

std::ostream& operator<<(std::ostream &out, const Moves &move) {
    out << move.getName();
    return out;
}