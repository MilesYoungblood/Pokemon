//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "Flamethrower.h"

Flamethrower::Flamethrower() : Move(15) {}

void Flamethrower::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->burnFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        this->burnFlag = binomial(10.0) and defender.getStatus() == StatusCondition::NONE;
        if (this->burnFlag) {
            defender.setStatus(StatusCondition::BURN);
        }
    }

    this->use();
}

std::queue<std::string> Flamethrower::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                     bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Flamethrower!" }};

    if (this->getDamageFlag() > 0) {
        messages.emplace("Flamethrower did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace("A critical hit!");
        }
        if (this->burnFlag) {
            messages.emplace(defender.getName() + " was burned!");
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string Flamethrower::getName() const {
    return "Flamethrower";
}

const char *Flamethrower::getDescription() const {
    return "The target is scorched with an intense blast of fire. It may also leave the target with a burn.";
}

int Flamethrower::getPower() const {
    return 95;
}

Type Flamethrower::getType() const {
    return Type::FIRE;
}

Move::Category Flamethrower::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id Flamethrower::getId() const {
    return Move::Id::FLAMETHROWER;
}
