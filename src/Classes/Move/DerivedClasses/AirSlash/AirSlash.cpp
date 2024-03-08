//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "AirSlash.h"

AirSlash::AirSlash() : Move(15) {}

void AirSlash::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());
    }

    this->use();

    skip = binomial(30.0);
}

std::vector<std::string> AirSlash::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool skip) const {
    std::vector<std::string> messages({ attacker.getName() + " used Air Slash!" });

    if (this->getDamageFlag() >= 0) {
        messages.push_back("Air Slash did " + std::to_string(this->getDamageFlag()) + " damage!");
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

std::string AirSlash::getName() const {
    return "Air Slash";
}

std::string AirSlash::getDescription() const {
    return "The user attacks with a blade of air that slices even the sky. It may also make the target flinch.";
}

int AirSlash::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 75;
}

int AirSlash::getAccuracy() const {
    return 95;
}

Type AirSlash::getType() const {
    return Type::FLYING;
}

Move::Category AirSlash::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id AirSlash::getId() const {
    return Move::Id::AIR_SLASH;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::AIR_SLASH,
                                      [] -> std::unique_ptr <Move> { return std::make_unique<AirSlash>(); }));
    });
}
