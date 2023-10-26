//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move(const int pp) : pp(pp), maxPp(pp) {}

int Move::getDamage() const {
    return generateInteger(1, 100) <= this->getAccuracy() ? this->getPower() : -1;
}

void Move::use() {
    if (this->pp > 0) {
        --this->pp;
    }
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

void Move::fillToMax() {
    this->pp = this->maxPp;
}

int Move::getPP() const {
    return this->pp;
}

int Move::getMaxPP() const {
    return this->maxPp;
}

int Move::getAccuracy() const {
    return 100;
}

Move::operator bool() const {
    return this->pp > 0;
}

std::ostream& operator<<(std::ostream &out, const Move &move) {
    out << move.getName();
    return out;
}
