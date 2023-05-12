//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move() {
    maxPp = 0;
    pp = 0;
    power = 0;
    accuracy = 0;
    type = "No type";
    category = "No category";
    name = "No name";
}

Move::Move(const std::string& name, const std::string& type, const std::string& category, int pp, int power, int accuracy) {
    maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->accuracy = accuracy;
    this->type = type;
    this->category = category;
    this->name = name;
}

Move::Move(const Move& moveToCopy) {
    pp = moveToCopy.pp;
    maxPp = moveToCopy.maxPp;
    power = moveToCopy.power;
    accuracy = moveToCopy.accuracy;
    type = moveToCopy.type;
    category = moveToCopy.category;
    name = moveToCopy.name;
}

int Move::getDamage() const {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    return dist(mt) <= accuracy ? power : -1;
}

int Move::getDamage() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    return dist(mt) <= accuracy ? power : -1;
}

void Move::setPP(int newPP) {
    pp = newPP;
}
int Move::getPP() const {
    return pp;
}

int Move::getMaxPP() const {
    return maxPp;
}

int Move::getPower() const {
    return power;
}

int Move::getAccuracy() const {
    return accuracy;
}

std::string Move::getType() const {
    return type;
}

std::string Move::getCategory() const {
    return category;
}

std::string Move::getName() const {
    return name;
}

bool Move::canUse() const {
    return pp > 0;
}

std::ostream& operator<<(std::ostream &out, const Move &move) {
    out << move.getName();
    return out;
}