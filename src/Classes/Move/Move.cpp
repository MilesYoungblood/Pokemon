//
// Created by miles on 5/5/2022.
//

#include "../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
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

void Move::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->damageFlag > 0) {
        defender.takeDamage(this->damageFlag);
    }

    this->use();
}

std::vector<std::string> Move::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool  /*skip*/) const {
    std::vector<std::string> messages({ attacker.getName() + " used " + this->getName() + '!' });

    if (this->damageFlag >= 0) {
        if (this->effFlag == 0.0) {
            messages.push_back("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.push_back(this->getName() + " did " + std::to_string(this->damageFlag) + " damage!");
            if (this->effFlag >= 2.0) {
                messages.emplace_back("It's super effective!");
            }
            else if (this->effFlag <= 0.5) {
                messages.emplace_back("It's not very effective...");
            }
            if (this->critFlag == 2.0) {
                messages.emplace_back("A critical hit!");
            }
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
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

bool Move::canUse() const {
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
    if (not binomial(static_cast<double>(this->getAccuracy()))) {
        // denotes a miss
        this->damageFlag = -1;
        return;
    }
    double initialDamage;

    const int level_calc = (2 * attacker.getLevel() / 5) + 2;
    switch (this->getCategory()) {
        case Category::PHYSICAL:
            initialDamage = level_calc * this->getPower(attacker, defender) *
                            attacker.getBaseStat(Pokemon::Stat::ATTACK) /
                            defender.getBaseStat(Pokemon::Stat::DEFENSE);
            break;
        case Category::SPECIAL:
            initialDamage = level_calc * this->getPower(attacker, defender) *
                            attacker.getBaseStat(Pokemon::Stat::SP_ATTACK) /
                            defender.getBaseStat(Pokemon::Stat::SP_DEFENSE);
            break;
        case Category::STATUS:
            return;
    }

    const double final_damage = initialDamage / 50 + 2;
    const double stab = this->getType() == attacker.getType1() or this->getType() == attacker.getType2() ? 1.5 : 1.0;

    this->effFlag = this->checkType(defender);
    this->critFlag = binomial(this->getCritRatio()) ? 2.0 : 1.0;

    //FIXME recalculate damage
    this->damageFlag = static_cast<int>(final_damage * stab * this->effFlag * this->critFlag);
}

double Move::checkType(const Pokemon &pokemon) const {
    static const int num_types = 17;

    static const std::array<std::array<double, num_types>, num_types> type_chart{
            {
                    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5 }, // normal
                    { 1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0 }, // fire
                    { 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0 }, // water
                    { 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0 }, // electric
                    { 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5 }, // grass
                    { 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5 }, // ice
                    { 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0 }, // fighting
                    { 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0 }, // poison
                    { 1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0 }, // ground
                    { 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5 }, // flying
                    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5 }, // psychic
                    { 1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5 }, // bug
                    { 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5 }, // rock
                    { 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // ghost
                    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5 }, // dragon
                    { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // dark
                    { 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5 }, // steel
            }
    };

    const int move_type = static_cast<int>(this->getType()) - 1;
    const double type_1 = type_chart.at(move_type).at(static_cast<int>(pokemon.getType1()) - 1);

    double type2;
    if (pokemon.getType2() == Type::NONE) {
        type2 = 1.0;
    }
    else {
        type2 = type_chart.at(move_type).at(static_cast<int>(pokemon.getType2()) - 1);
    }

    return type_1 * type2;
}
