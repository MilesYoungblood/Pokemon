//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "Flamethrower.h"

Flamethrower::Flamethrower() : Move(15) {}

void Flamethrower::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->burnFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        this->burnFlag = binomial(10.0) and defender.getStatus() == StatusCondition::NONE;
        if (this->burnFlag) {
            defender.setStatus(StatusCondition::BURN);
        }
    }

    this->use();
}

std::vector<std::string> Flamethrower::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                      bool  /*skip*/) const {
    std::vector<std::string> messages({ attacker.getName() + " used Flamethrower!" });

    if (this->getDamageFlag() >= 0) {
        messages.push_back("Flamethrower did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        if (this->burnFlag) {
            messages.push_back(defender.getName() + " was burned!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string Flamethrower::getName() const {
    return "Flamethrower";
}

std::string Flamethrower::getDescription() const {
    return "The target is scorched with an intense blast of fire. It may also leave the target with a burn.";
}

int Flamethrower::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 95;
}

Type Flamethrower::getType() const {
    return Type::FIRE;
}

Move::Category Flamethrower::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id Flamethrower::getId() const {
    return Move::Id::FLAMETHROWER;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::FLAMETHROWER,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<Flamethrower>(); }));
    });
}
