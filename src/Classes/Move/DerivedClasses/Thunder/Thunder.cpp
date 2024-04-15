//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../../Functions/GeneralFunctions.h"
#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "Thunder.h"

Thunder::Thunder() : Move(10) {}

void Thunder::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();
    this->paralysisFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.getHp().lower(this->getDamageFlag());

        this->paralysisFlag = binomial(10.0) and defender.getStatus() == StatusCondition::NONE;
        if (this->paralysisFlag) {
            defender.setStatus(StatusCondition::PARALYSIS);
        }
    }

    this->getPp().lower(1);
}

std::vector<std::string> Thunder::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                 bool  /*skip*/) const {
    std::vector messages({ attacker.getName() + " used Thunder!" });

    if (this->getDamageFlag() >= 0) {
        if (this->getEffFlag() == 0.0) {
            messages.push_back("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.push_back("Thunder did " + std::to_string(this->getDamageFlag()) + " damage!");
            if (this->getEffFlag() >= 2.0) {
                messages.emplace_back("It's super effective!");
            }
            else if (this->getEffFlag() <= 0.5) {
                messages.emplace_back("It's not very effective...");
            }
            if (this->getCritFlag() == 2.0) {
                messages.emplace_back("A critical hit!");
            }
            if (this->paralysisFlag) {
                messages.push_back(defender.getName() + " was paralyzed!");
            }
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string Thunder::getName() const {
    return "Thunder";
}

std::string Thunder::getDescription() const {
    return "A wicked thunderbolt is dropped on the target to inflict damage. It may also leave the target with paralysis.";
}

int Thunder::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 120;
}

int Thunder::getAccuracy() const {
    return 70;
}

Type Thunder::getType() const {
    return Type::ELECTRIC;
}

Move::Category Thunder::getCategory() const {
    return Category::SPECIAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Thunder"] = [] -> std::unique_ptr<Move> { return std::make_unique<Thunder>(); };
    });
}
