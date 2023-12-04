//
// Created by Miles Youngblood on 12/3/2023.
//

#pragma once

#include "../../Ability.h"

struct Intimidate : public Ability {
    void action(Pokemon &attacker, Pokemon &defender) override;

    [[nodiscard]] std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] int getFlag() const override;
};

inline AutoThread init([] -> void {
    abilityMap.insert(std::make_pair(Ability::Id::INTIMIDATE,
                                     [] -> std::unique_ptr<Ability> { return std::make_unique<Intimidate>(); }));
});
