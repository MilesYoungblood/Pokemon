//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../../Functions/GeneralFunctions.h"
#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "IceBeam.h"

IceBeam::IceBeam() : Move(10) {}

void IceBeam::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->freezeFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        this->freezeFlag = binomial(10.0) and defender.getStatus() == StatusCondition::NONE;
        if (this->freezeFlag) {
            defender.setStatus(StatusCondition::FREEZE);
        }
    }

    this->use();
}

std::vector<std::string> IceBeam::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                 bool  /*skipTurn*/) const {
    std::vector<std::string> messages({ attacker.getName() + " used Ice Beam!" });

    if (this->getDamageFlag() > 0) {
        messages.push_back("Ice Beam did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        if (this->freezeFlag) {
            messages.push_back(defender.getName() + " became frozen!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string IceBeam::getName() const {
    return "Ice Beam";
}

std::string IceBeam::getDescription() const {
    return "The target is struck with an icy-cold beam of energy. It may also freeze the target solid.";
}

int IceBeam::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 95;
}

Type IceBeam::getType() const {
    return Type::ICE;
}

Move::Category IceBeam::getCategory() const {
    return Move::Category::SPECIAL;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap["Ice Beam"] = [] -> std::unique_ptr<Move> { return std::make_unique<IceBeam>(); };
    });
}
