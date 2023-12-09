//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
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

std::queue<std::string> IceBeam::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                bool  /*skipTurn*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Ice Beam!" }};

    if (this->getDamageFlag() > 0) {
        messages.emplace("Ice Beam did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace("A critical hit!");
        }
        if (this->freezeFlag) {
            messages.emplace(defender.getName() + " became frozen!");
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string IceBeam::getName() const {
    return "Ice Beam";
}

const char *IceBeam::getDescription() const {
    return "The target is struck with an icy-cold beam of energy. It may also freeze the target solid.";
}

int IceBeam::getPower() const {
    return 95;
}

Type IceBeam::getType() const {
    return Type::ICE;
}

Move::Category IceBeam::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id IceBeam::getId() const {
    return Move::Id::ICE_BEAM;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::ICE_BEAM,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<IceBeam>(); }));
    });
}
