//
// Created by Miles Youngblood on 12/3/2023.
//

#include "../../../Entity/DerivedClasses/Pokemon/Pokemon.h"
#include "Intimidate.h"

void Intimidate::action(Pokemon & /*attacker*/, Pokemon &defender) {
    defender.lowerStatMod(Pokemon::Stat::ATTACK, 1);
}

std::queue<std::string> Intimidate::actionMessage(const Pokemon & /*attacker*/, const Pokemon &defender) const {
    return std::queue<std::string>({ defender.getName() + "'s attack was lowered!" });
}

int Intimidate::getFlag() const {
    return -1;
}
