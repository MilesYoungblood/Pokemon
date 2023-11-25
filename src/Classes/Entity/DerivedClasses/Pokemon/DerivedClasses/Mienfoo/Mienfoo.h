//
// Created by Miles on 11/24/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Mienfoo : public Pokemon {
    Mienfoo();

    Mienfoo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] Type getType(bool type1) const override;

    [[nodiscard]] int getCatchRate() const override;

    [[nodiscard]] Pokemon::Id getId() const override;
};
