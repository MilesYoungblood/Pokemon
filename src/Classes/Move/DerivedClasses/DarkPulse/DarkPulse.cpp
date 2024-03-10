//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Character/DerivedClasses/Pokemon/Pokemon.h"
#include "DarkPulse.h"

DarkPulse::DarkPulse() : Move(15) {}

void DarkPulse::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());
    }

    this->use();

    skip = binomial(20.0);
}

std::vector<std::string> DarkPulse::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const {
    std::vector<std::string> messages({ attacker.getName() + " used Dark Pulse!" });

    if (this->getDamageFlag() > 0) {
        messages.push_back("Dark Pulse did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        if (skip) {
            messages.push_back(defender.getName() + " flinched!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string DarkPulse::getName() const {
    return "Dark Pulse";
}

std::string DarkPulse::getDescription() const {
    return "The user releases a horrible aura imbued with dark thoughts. It may also make the target flinch.";
}

int DarkPulse::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 80;
}

Type DarkPulse::getType() const {
    return Type::DARK;
}

Move::Category DarkPulse::getCategory() const {
    return Move::Category::SPECIAL;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap["Dark Pulse"] = [] -> std::unique_ptr<Move> { return std::make_unique<DarkPulse>(); };
    });
}
