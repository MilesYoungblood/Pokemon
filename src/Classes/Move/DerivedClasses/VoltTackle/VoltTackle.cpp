//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "VoltTackle.h"

VoltTackle::VoltTackle() : Move(15) {}

void VoltTackle::action(Pokemon &attacker, Pokemon &defender, bool &skip) {
    this->resetFlags();
    this->paralysisFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());
        attacker.takeDamage(static_cast<int>(lround(this->getDamageFlag() / 3.0)));

        //FIXME faint Pokemon if necessary
        if (attacker.isFainted()) {
            // TODO trigger switch out back at the battle
        }

        this->paralysisFlag = generateInteger(1, 10) == 1 and defender.getStatus() == StatusCondition::NONE;
        if (this->paralysisFlag) {
            defender.setStatus(StatusCondition::PARALYSIS);
        }
    }

    this->use();
}

std::queue<std::string> VoltTackle::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                   bool  /*skip*/) const {
    std::queue<std::string> messages{{ attacker.getName() + " used Volt Tackle!" }};

    if (this->getDamageFlag() > 0) {
        if (this->getEffFlag() == 0.0) {
            messages.emplace("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.emplace("Volt Tackle did " + std::to_string(this->getDamageFlag()) + " damage!");
            if (this->getEffFlag() >= 2.0) {
                messages.emplace("It's super effective!");
            }
            else if (this->getEffFlag() <= 0.5) {
                messages.emplace("It's not very effective...");
            }
            if (this->getCritFlag() == 2.0) {
                messages.emplace("A critical hit!");
            }
            if (this->paralysisFlag) {
                messages.emplace(defender.getName() + " was paralyzed!");
            }
            messages.emplace(
                    attacker.getName() + " took " + static_cast<int>(lround(this->getDamageFlag() / 3.0)) + " damage!");

            if (attacker.isFainted()) {
                messages.emplace(attacker.getName() + " fainted!");
            }
        }
    }
    else {
        messages.emplace(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string VoltTackle::getName() const {
    return "Volt Tackle";
}

const char *VoltTackle::getDescription() const {
    return "The user electrifies itself, then charges. It causes considerable damage to the user and may leave the target with paralysis.";
}

int VoltTackle::getPower() const {
    return 120;
}

Type VoltTackle::getType() const {
    return Type::ELECTRIC;
}

Move::Category VoltTackle::getCategory() const {
    return Move::Category::PHYSICAL;
}

Move::Id VoltTackle::getId() const {
    return Move::Id::VOLT_TACKLE;
}
