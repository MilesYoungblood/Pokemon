//
// Created by Miles Youngblood on 12/3/2023.
//

#include "Ability.h"

std::queue<std::string> Ability::actionMessage(const Pokemon & /*attacker*/, const Pokemon & /*defender*/) const {
    return {};
}

bool Ability::isBattle() const {
    return true;
}
