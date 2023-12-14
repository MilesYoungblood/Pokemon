//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "Extrasensory.h"

Extrasensory::Extrasensory() : Move(30) {}

void Extrasensory::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());
    }

    this->use();

    skip = binomial(10.0);
}

std::queue<std::string> Extrasensory::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                     bool skip) const {
    std::queue<std::string> messages({ attacker.getName() + " used Extrasensory!" });

    if (this->getDamageFlag() > 0) {
        if (this->getEffFlag() == 0.0) {
            messages.emplace("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.emplace("Extrasensory did " + std::to_string(this->getDamageFlag()) + " damage!");
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
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string Extrasensory::getName() const {
    return "Extrasensory";
}

const char *Extrasensory::getDescription() const {
    return "The user attacks with an odd, unseeable power. It may also make the target flinch.";
}

int Extrasensory::getPower() const {
    return 80;
}

Type Extrasensory::getType() const {
    return Type::PSYCHIC;
}

Move::Category Extrasensory::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id Extrasensory::getId() const {
    return Move::Id::EXTRASENSORY;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::EXTRASENSORY,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<Extrasensory>(); }));
    });
}
