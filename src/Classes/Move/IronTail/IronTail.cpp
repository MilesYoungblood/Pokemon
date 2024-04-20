//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../../utility/Functions/GeneralFunctions.h"
#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "IronTail.h"

IronTail::IronTail() : Move(15) {}

void IronTail::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->loweredFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.getHp().lower(this->getDamageFlag());

        //FIXME redo calculations
        this->loweredFlag = binomial(10.0) and defender.getStatMod(Pokemon::Stat::DEFENSE) > -6;

        //FIXME account for limit reached
        if (this->loweredFlag) {
            defender.lowerStatMod(Pokemon::Stat::DEFENSE, 1);
        }
    }

    this->getPp().lower(1);
}

std::vector<std::string> IronTail::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                  bool  /*skip*/) const {
    std::vector messages({ attacker.getName() + " used Iron Tail!" });

    if (this->getDamageFlag() > 0) {
        messages.push_back("Iron Tail did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        if (this->loweredFlag) {
            messages.push_back(defender.getName() + "'s defense was lowered!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string IronTail::getName() const {
    return "Iron Tail";
}

std::string IronTail::getDescription() const {
    return "The target is slammed with a steel-hard tail. It may also lower the target’s Defense stat.";
}

int IronTail::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 100;
}

int IronTail::getAccuracy() const {
    return 75;
}

Type IronTail::getType() const {
    return Type::STEEL;
}

Move::Category IronTail::getCategory() const {
    return Category::PHYSICAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Iron Tail"] = [] -> std::unique_ptr<Move> { return std::make_unique<IronTail>(); };
    });
}
