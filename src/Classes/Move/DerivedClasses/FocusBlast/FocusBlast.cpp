//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "FocusBlast.h"

FocusBlast::FocusBlast() : Move(5) {}

void FocusBlast::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->loweredFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());

        this->loweredFlag = binomial(10.0) and defender.getStatMod(Pokemon::Stat::SP_DEFENSE) > -6;

        if (this->loweredFlag) {
            defender.lowerStatMod(Pokemon::Stat::SP_DEFENSE, 1);
        }
    }

    this->use();
}

std::queue<std::string> FocusBlast::actionMessage(const Pokemon &attacker, const Pokemon &defender, bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Focus Blast!" }};

    if (this->getDamageFlag() > 0) {
        if (this->getEffFlag() == 0.0) {
            messages.emplace("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.emplace("Focus Blast did " + std::to_string(this->getDamageFlag()) + " damage!");
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
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string FocusBlast::getName() const {
    return "Focus Blast";
}

const char *FocusBlast::getDescription() const {
    return "The user heightens its mental focus and unleashes its power. It may also lower the target’s Sp. Def.";
}

int FocusBlast::getPower() const {
    return 120;
}

int FocusBlast::getAccuracy() const {
    return 70;
}

Type FocusBlast::getType() const {
    return Type::FIGHTING;
}

Move::Category FocusBlast::getCategory() const {
    return Move::Category::SPECIAL;
}

Move::Id FocusBlast::getId() const {
    return Move::Id::FOCUS_BLAST;
}
