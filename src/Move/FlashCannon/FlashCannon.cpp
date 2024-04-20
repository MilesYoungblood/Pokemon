//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "FlashCannon.h"

FlashCannon::FlashCannon() : Move(10) {}

void FlashCannon::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->loweredFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.getHp().lower(this->getDamageFlag());

        /*
        //FIXME redo calculations
        this->loweredFlag = binomial(10.0) and defender.getStatMod(Pokemon::Stat::SP_DEFENSE) > -6;

        if (this->loweredFlag) {
            defender.lowerStatMod(Pokemon::Stat::SP_DEFENSE, 1);
        }
        */
    }

    this->getPp().lower(1);
}

std::vector<std::string> FlashCannon::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                     bool  /*skip*/) const {
    std::vector messages({ attacker.getName() + " used Flash Cannon!" });

    if (this->getDamageFlag() >= 0) {
        messages.push_back("Flash Cannon did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        if (this->loweredFlag) {
            messages.emplace_back(defender.getName() + "'s special defense was lowered!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string FlashCannon::getName() const {
    return "Flash Cannon";
}

std::string FlashCannon::getDescription() const {
    return "The user gathers all its light energy and releases it at once. It may also lower the target’s Sp. Def stat.";
}

int FlashCannon::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 80;
}

Type FlashCannon::getType() const {
    return Type::STEEL;
}

Move::Category FlashCannon::getCategory() const {
    return Category::SPECIAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Flash Cannon"] = [] -> std::unique_ptr<Move> { return std::make_unique<FlashCannon>(); };
    });
}
