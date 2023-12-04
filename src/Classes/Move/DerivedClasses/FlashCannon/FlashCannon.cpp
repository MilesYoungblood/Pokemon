//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "FlashCannon.h"

FlashCannon::FlashCannon() : Move(10) {}

void FlashCannon::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->loweredFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        //FIXME redo calculations
        this->loweredFlag = binomial(10.0) and defender.getStatMod(Pokemon::Stat::SP_DEFENSE) > -6;

        if (this->loweredFlag) {
            defender.lowerStatMod(Pokemon::Stat::SP_DEFENSE, 1);
        }
    }

    this->use();
}

std::queue<std::string> FlashCannon::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Flash Cannon!" }};

    if (this->getDamageFlag() > 0) {
        messages.emplace("Flash Cannon did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace("It's not very effective...");
        }
        if (this->getCritFlag()) {
            messages.emplace("A critical hit!");
        }
        if (this->loweredFlag) {
            messages.emplace(defender.getName() + "'s special defense was lowered!");
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string FlashCannon::getName() const {
    return "Flash Cannon";
}

const char *FlashCannon::getDescription() const {
    return "The user gathers all its light energy and releases it at once. It may also lower the target’s Sp. Def stat.";
}

int FlashCannon::getPower() const {
    return 80;
}

Type FlashCannon::getType() const {
    return Type::STEEL;
}

Move::Category FlashCannon::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id FlashCannon::getId() const {
    return Move::Id::FLASH_CANNON;
}
