//
// Created by miles on 5/5/2022.
//

#include "Move.h"

Move::Move(Move::Id id) : id(id), pp(0), maxPp(0) {
    if (Move::dataFunction == nullptr) {
        throw std::runtime_error("Tried to construct Move without initializing class\n");
    }
}

Move::Move(Move::Id id, int pp, int maxPp) : id(id), pp(pp), maxPp(maxPp) {
    if (Move::dataFunction == nullptr) {
        throw std::runtime_error("Tried to construct Move without initializing class\n");
    }
}

int Move::getDamage() const {
    return generateInteger(1, 100) <= this->getAccuracy() ? this->getPower() : -1;
}

Move::Move(Move &&toMove) noexcept : id(toMove.id), pp(toMove.pp), maxPp(toMove.maxPp) {}

Move &Move::operator=(Move &&rhs) noexcept {
    this->id = rhs.id;
    this->pp = rhs.pp;
    this->maxPp = rhs.maxPp;

    return *this;
}

void Move::initData(Move::Data (*instructions)(Move::Id)) {
    static bool initialized = false;

    if (initialized) {
        return;
    }

    Move::dataFunction = instructions;
    initialized = true;
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

std::string Move::getName() const {
    return std::string(Move::dataFunction(this->id).name);
}

const char *Move::getDescription() const {
    return Move::dataFunction(this->id).description.data();
}

int Move::getPower() const {
    return Move::dataFunction(this->id).power;
}

int Move::getAccuracy() const {
    return Move::dataFunction(this->id).accuracy;
}

Type Move::getType() const {
    return Move::dataFunction(this->id).type;
}

Move::Category Move::getCategory() const {
    return Move::dataFunction(this->id).category;
}

bool Move::isPriority() const {
    return Move::dataFunction(this->id).priority;
}

Move::Id Move::getId() const {
    return this->id;
}

Move::operator bool() const {
    return this->pp > 0;
}
