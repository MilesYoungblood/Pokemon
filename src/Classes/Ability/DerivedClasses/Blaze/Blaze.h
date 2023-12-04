//
// Created by Miles Youngblood on 12/3/2023.
//

#pragma once

#include "../../Ability.h"

struct Blaze : public Ability {
    void action(Pokemon &attacker, Pokemon &defender) override {
        // TODO to be done in move class specifically; make power a field
    }

    [[nodiscard]] int getFlag() const override {
        return -1;
    }
};

inline AutoThread init([] -> void {
    abilityMap.insert(
            std::make_pair(Ability::Id::BLAZE, [] -> std::unique_ptr<Ability> { return std::make_unique<Blaze>(); }));
});
