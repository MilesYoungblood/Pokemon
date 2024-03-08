//
// Created by Miles Youngblood on 12/3/2023.
//

#include "Blaze.h"

void Blaze::action(Pokemon &attacker, Pokemon &defender) {
    // TODO to be done in move class specifically; make power a field
}

int Blaze::getFlag() const {
    return -1;
}

Ability::Id Blaze::getId() const {
    return Ability::Id::BLAZE;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(abilityMutex);
        abilityMap.insert(
                std::make_pair(Ability::Id::BLAZE,
                               [] -> std::unique_ptr<Ability> { return std::make_unique<Blaze>(); }));
    });
}
