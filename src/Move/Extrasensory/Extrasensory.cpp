//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../../utility/Functions/GeneralFunctions.h"
#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "Extrasensory.h"

Extrasensory::Extrasensory() : Move(30) {}

void Extrasensory::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.getHp().lower(this->getDamageFlag());
    }

    this->getPp().lower(1);

    skip = binomial(10.0);
}

std::vector<std::string> Extrasensory::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                     const bool skip) const {
    std::vector messages({ attacker.getName() + " used Extrasensory!" });

    if (this->getDamageFlag() >= 0) {
        if (this->getEffFlag() == 0.0) {
            messages.push_back("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.push_back("Extrasensory did " + std::to_string(this->getDamageFlag()) + " damage!");
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
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string Extrasensory::getName() const {
    return "Extrasensory";
}

std::string Extrasensory::getDescription() const {
    return "The user attacks with an odd, unseeable power. It may also make the target flinch.";
}

int Extrasensory::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 80;
}

Type Extrasensory::getType() const {
    return Type::PSYCHIC;
}

Move::Category Extrasensory::getCategory() const {
    return Category::SPECIAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Extrasensory"] = [] -> std::unique_ptr<Move> { return std::make_unique<Extrasensory>(); };
    });
}
