//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move(const int pp) : pp(pp), maxPp(pp) {}

Move::Move(const int pp, const int maxPp) : pp(pp), maxPp(maxPp) {}

int Move::getDamage() const {
    return generateInteger(1, 100) <= this->getAccuracy() ? this->getPower() : -1;
}

void Move::restore(int amount) {
    this->pp = std::min(this->pp + amount, this->maxPp);
}

void Move::use() {
    this->pp = std::max(this->pp - 1, 0);
}

int Move::getPp() const {
    return this->pp;
}

int Move::getMaxPp() const {
    return this->maxPp;
}

void Move::fillToMax() {
    this->pp = maxPp;
}

int Move::getAccuracy() const {
    return 100;
}

bool Move::isPriority() const {
    return false;
}

Move::operator bool() const {
    return this->pp > 0;
}
