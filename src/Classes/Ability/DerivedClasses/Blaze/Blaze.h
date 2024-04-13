//
// Created by Miles Youngblood on 12/3/2023.
//

#pragma once

#include "../../Ability.h"

struct Blaze : public Ability {
    void action(Pokemon &attacker, Pokemon &defender) override;

    [[nodiscard]] int getFlag() const override;

    [[nodiscard]] Ability::Id getId() const override;
};
