//
// Created by miles on 5/5/2022.
//

#include "../../../utility/Functions/GeneralFunctions.h"
#include "../Entity/Character/Pokemon/Pokemon.h"
#include "Move.h"

Move::Move(const int pp) : pp(pp, pp) {}

Move::Move(const int pp, const int maxPp) : pp(pp, maxPp) {}

Component::Resource &Move::getPp() {
    return this->pp;
}

Component::Resource Move::getPp() const {
    return this->pp;
}

void Move::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->damageFlag > 0) {
        defender.getHp().lower(this->damageFlag);
    }

    this->pp.lower(1);
}

std::vector<std::string> Move::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool  /*skip*/) const {
    std::vector messages({ attacker.getName() + " used " + this->getName() + '!' });

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
    return not this->pp.empty();
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
    if (not binomial(this->getAccuracy())) {
        // denotes a miss
        this->damageFlag = -1;
        return;
    }
    double initialDamage = 0.0;

    double burnFlag = 1.0;
    const int levelCalc = 2 * attacker.getLevel() / 5 + 2;
    switch (this->getCategory()) {
        case Category::PHYSICAL:
            initialDamage = levelCalc * this->getPower(attacker, defender) * attacker.getBaseStat("Attack") /
                            defender.getBaseStat("Defense");
            if (attacker.getStatus() == StatusCondition::BURN) {
                burnFlag = 0.5;
            }
            break;
        case Category::SPECIAL:
            initialDamage = levelCalc * this->getPower(attacker, defender) * attacker.getBaseStat("Sp. Attack") /
                            defender.getBaseStat("Sp. Defense");
            break;
        case Category::STATUS:
            return;
    }

    const double finalDamage = initialDamage / 50 + 2;
    const double stab = this->getType() == attacker.getType1() or this->getType() == attacker.getType2() ? 1.5 : 1.0;

    this->effFlag = this->checkType(defender);
    this->critFlag = binomial(this->getCritRatio()) ? 2.0 : 1.0;

    //FIXME recalculate damage
    this->damageFlag = static_cast<int>(finalDamage * stab * this->effFlag * this->critFlag * burnFlag);
}

double Move::checkType(const Pokemon &pokemon) const {
    constexpr int numTypes = 17;

    // x-axis is defender, y-axis is attacker
    constexpr std::array<std::array<double, numTypes>, numTypes> typeChart{
            {       // normal, fire, water, electric, grass, ice, fighting, poison, ground, flying, psychic, ..., steel
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

    // -1 because Type::NONE is 0 rather than Type::NORMAL
    const int moveType = static_cast<int>(this->getType()) - 1;
    const double type1 = typeChart.at(moveType).at(static_cast<int>(pokemon.getType1()) - 1);

    double type2;
    if (pokemon.getType2() == Type::NONE) {
        type2 = 1.0;
    }
    else {
        type2 = typeChart.at(moveType).at(static_cast<int>(pokemon.getType2()) - 1);
    }

    return type1 * type2;
}
