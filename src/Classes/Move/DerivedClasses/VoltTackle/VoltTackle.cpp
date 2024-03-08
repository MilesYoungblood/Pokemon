//
// Created by Miles Youngblood on 12/4/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "VoltTackle.h"

VoltTackle::VoltTackle() : Move(15) {}

void VoltTackle::action(Pokemon &attacker, Pokemon &defender, bool & /*skip*/) {
    this->resetFlags();
    this->paralysisFlag = false;

    this->calculateDamage(attacker, defender);
    // damage will be negative if the attack misses
    if (this->getDamageFlag() > 0) {
        defender.takeDamage(this->getDamageFlag());
        attacker.takeDamage(static_cast<int>(std::round(this->getDamageFlag() / 3.0)));

        //FIXME faint Pokemon if necessary
        if (attacker.isFainted()) {
            // TODO trigger switch out back at the battle
        }

        this->paralysisFlag = binomial(10.0) and defender.getStatus() == StatusCondition::NONE;
        if (this->paralysisFlag) {
            defender.setStatus(StatusCondition::PARALYSIS);
        }
    }

    this->use();
}

std::vector<std::string> VoltTackle::actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                    bool  /*skip*/) const {
    std::vector<std::string> messages({ attacker.getName() + " used Volt Tackle!" });

    if (this->getDamageFlag() > 0) {
        if (this->getEffFlag() == 0.0) {
            messages.push_back("It doesn't affect " + defender.getName() + "...");
        }
        else {
            messages.push_back("Volt Tackle did " + std::to_string(this->getDamageFlag()) + " damage!");
            if (this->getEffFlag() >= 2.0) {
                messages.emplace_back("It's super effective!");
            }
            else if (this->getEffFlag() <= 0.5) {
                messages.emplace_back("It's not very effective...");
            }
            if (this->getCritFlag() == 2.0) {
                messages.emplace_back("A critical hit!");
            }
            if (this->paralysisFlag) {
                messages.push_back(defender.getName() + " was paralyzed!");
            }
            messages.push_back(attacker.getName() + " took " + static_cast<int>(std::round(this->getDamageFlag() / 3.0))
                               + " damage!");

            if (attacker.isFainted()) {
                messages.push_back(attacker.getName() + " fainted!");
            }
        }
    }
    else {
        messages.push_back(defender.getName() + " avoided the attack!");
    }

    return messages;
}

std::string VoltTackle::getName() const {
    return "Volt Tackle";
}

std::string VoltTackle::getDescription() const {
    return "The user electrifies itself, then charges. It causes considerable damage to the user and may leave the target with paralysis.";
}

int VoltTackle::getPower(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::VOLT_TACKLE,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<VoltTackle>(); }));
    });
}
