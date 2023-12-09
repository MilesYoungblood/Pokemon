//
// Created by miles on 5/5/2022.
//

#include "../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "Move.h"

Move::Move(int pp) : pp(pp), maxPp(pp) {}

Move::Move(int pp, int maxPp) : pp(pp), maxPp(maxPp) {}

void Move::setPp(int amount) {
    this->pp = std::min(amount, this->maxPp);
    this->pp = std::max(amount, 0);
}

void Move::setMaxPp(int amount) {
    // TODO add bounds to max PP
    this->maxPp = std::max(amount, 0);
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

int Move::getDamage() const {
    return binomial(static_cast<double>(this->getAccuracy())) ? this->getPower() : -1;
}

void Move::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->damageFlag > 0) {
        defender.takeDamage(this->damageFlag);
    }

    this->use();
}

std::queue<std::string> Move::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used " + this->getName() + '!' }};

    if (this->damageFlag > 0) {
        if (this->effFlag == 0.0) {
            messages.emplace("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.emplace(this->getName() + " did " + std::to_string(this->damageFlag) + " damage!");
            if (this->effFlag >= 2.0) {
                messages.emplace("It's super effective!");
            }
            else if (this->effFlag <= 0.5) {
                messages.emplace("It's not very effective...");
            }
            if (this->critFlag == 2.0) {
                messages.emplace("A critical hit!");
            }
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

int Move::getAccuracy() const {
    return 100;
}

double Move::getCritRatio() const {
    return 6.25;
}

bool Move::isPriority() const {
    return false;
}

Move::operator bool() const {
    return this->pp > 0;
}

void Move::resetFlags() {
    this->damageFlag = 0;
    this->effFlag = 0.0;
    this->critFlag = 0.0;
}

int Move::getDamageFlag() const {
    return this->damageFlag;
}

double Move::getEffFlag() const {
    return this->effFlag;
}

double Move::getCritFlag() const {
    return this->critFlag;
}

void Move::calculateDamage(const Pokemon &attacker, const Pokemon &defender) {
    double initialDamage{ 0.0 };

    const int level_calc = (2 * attacker.getLevel() / 5) + 2;
    if (this->getCategory() == Move::Category::PHYSICAL) {
        initialDamage = level_calc * this->getDamage() * attacker.getBaseStat(Pokemon::Stat::ATTACK) /
                        defender.getBaseStat(Pokemon::Stat::DEFENSE);
    }
    else if (this->getCategory() == Move::Category::SPECIAL) {
        initialDamage = level_calc * this->getDamage() * attacker.getStatMod(Pokemon::Stat::SP_ATTACK) /
                        defender.getBaseStat(Pokemon::Stat::SP_DEFENSE);
    }

    const double final_damage = initialDamage / 50 + 2;
    const double stab = this->getType() == attacker.getType(true) or this->getType() == attacker.getType(false) ? 1.5 : 1.0;

    this->effFlag = this->checkType(attacker);
    this->critFlag = binomial(this->getCritRatio()) ? 2.0 : 1.0;

    //FIXME recalculate damage
    this->damageFlag = static_cast<int>(final_damage * stab * this->effFlag * this->critFlag);
}

double Move::checkType(const Pokemon &pokemon) const {
    static const int num_types = 17;

    static const std::array<std::array<double, num_types>, num_types> type_chart = {
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5 }, // normal
            std::array<double, num_types>{ 1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0 }, // fire
            std::array<double, num_types>{ 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0 }, // water
            std::array<double, num_types>{ 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0 }, // electric
            std::array<double, num_types>{ 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5 }, // grass
            std::array<double, num_types>{ 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5 }, // ice
            std::array<double, num_types>{ 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0 }, // fighting
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0 }, // poison
            std::array<double, num_types>{ 1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0 }, // ground
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5 }, // flying
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5 }, // psychic
            std::array<double, num_types>{ 1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5 }, // bug
            std::array<double, num_types>{ 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5 }, // rock
            std::array<double, num_types>{ 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // ghost
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5 }, // dragon
            std::array<double, num_types>{ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // dark
            std::array<double, num_types>{ 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5 }, // steel
    };

    const int move_type = static_cast<int>(this->getType()) - 1;
    const double type_1 = type_chart.at(move_type).at(static_cast<int>(pokemon.getType(true)) - 1);

    double type2;
    if (pokemon.getType(false) == Type::NONE) {
        type2 = 1.0;
    }
    else {
        type2 = type_chart.at(move_type).at(static_cast<int>(pokemon.getType(false)) - 1);
    }

    return type_1 * type2;
}
