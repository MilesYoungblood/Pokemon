//
// Created by Miles Youngblood on 3/4/2024.
//

#include "../../Entity/Character/Pokemon/Pokemon.h"
#include "HeadSmash.h"

HeadSmash::HeadSmash() : Move(5) {}

void HeadSmash::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.getHp().lower(this->getDamageFlag());
        attacker.getHp().lower(static_cast<int>(std::round(this->getDamageFlag() / 2.0)));

        //FIXME faint Pokemon if necessary
        if (attacker.getHp().empty()) {
            // TODO trigger switch out back at the battle
        }
    }

    this->getPp().lower(1);
}

std::vector<std::string> HeadSmash::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                   bool  /*skipTurn*/) const {
    std::vector messages({ attacker.getName() + " used Head Smash!" });

    if (this->getDamageFlag() >= 0) {
        messages.push_back("Head Smash did " + std::to_string(this->getDamageFlag()) + " damage!");
        if (this->getEffFlag() >= 2.0) {
            messages.emplace_back("It's super effective!");
        }
        else if (this->getEffFlag() <= 0.5) {
            messages.emplace_back("It's not very effective...");
        }
        if (this->getCritFlag() == 2.0) {
            messages.emplace_back("A critical hit!");
        }
        messages.push_back(attacker.getName() + " took " + std::to_string(static_cast<int>(std::round(this->getDamageFlag() / 2.0))) +
                           " damage from recoil!");

        if (attacker.getHp().empty()) {
            messages.push_back(attacker.getName() + " fainted!");
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string HeadSmash::getName() const {
    return "Head Smash";
}

std::string HeadSmash::getDescription() const {
    return "The target is struck with an icy-cold beam of energy. It may also freeze the target solid.";
}

int HeadSmash::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return 150;
}

int HeadSmash::getAccuracy() const {
    return 80;
}

Type HeadSmash::getType() const {
    return Type::ROCK;
}

Move::Category HeadSmash::getCategory() const {
    return Category::PHYSICAL;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(moveMutex);
        moveMap["Head Smash"] = [] -> std::unique_ptr<Move> { return std::make_unique<HeadSmash>(); };
    });
}
