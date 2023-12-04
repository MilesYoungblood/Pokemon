//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
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

std::queue<std::string> DarkPulse::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Dark Pulse!" }};

    if (this->getDamageFlag() > 0) {
        messages.emplace("Dark Pulse did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace("A critical hit!");
        }
        if (skip) {
            messages.emplace(defender.getName() + " flinched!");
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string DarkPulse::getName() const {
    return "Dark Pulse";
}

const char *DarkPulse::getDescription() const {
    return "The user releases a horrible aura imbued with dark thoughts. It may also make the target flinch.";
}

int DarkPulse::getPower() const {
    return 80;
}

Type DarkPulse::getType() const {
    return Type::DARK;
}

Move::Category DarkPulse::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id DarkPulse::getId() const {
    return Move::Id::DARK_PULSE;
}
