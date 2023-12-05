//
// Created by Miles Youngblood on 12/3/2023.
//

#include "Ability.h"

std::queue<std::string> Ability::actionMessage(const Pokemon &attacker, const Pokemon &defender) const {
    return std::queue<std::string>();
}

bool Ability::isBattle() const {
    return true;
}

std::unordered_map<Ability::Id, std::unique_ptr<Ability>(*)()> abilityMap;