//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "IronTail.h"

IronTail::IronTail() : Move(15) {}

void IronTail::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->loweredFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        //FIXME redo calculations
        this->loweredFlag = binomial(10.0) and defender.getStatMod(Pokemon::Stat::DEFENSE) > -6;

        //FIXME account for limit reached
        if (this->loweredFlag) {
            defender.lowerStatMod(Pokemon::Stat::DEFENSE, 1);
        }
    }

    this->use();
}

std::queue<std::string> IronTail::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                 bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Iron Tail!" }};

    if (this->getDamageFlag() > 0) {
        messages.emplace("Iron Tail did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace("A critical hit!");
        }
        if (this->loweredFlag) {
            messages.emplace(defender.getName() + "'s defense was lowered!");
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string IronTail::getName() const {
    return "Iron Tail";
}

const char *IronTail::getDescription() const {
    return "The target is slammed with a steel-hard tail. It may also lower the target’s Defense stat.";
}

int IronTail::getPower() const {
    return 100;
}

int IronTail::getAccuracy() const {
    return 75;
}

Type IronTail::getType() const {
    return Type::STEEL;
}

Move::Category IronTail::getCategory() const {
    return Move::Category::PHYSICAL;
}

Move::Id IronTail::getId() const {
    return Move::Id::IRON_TAIL;
}
