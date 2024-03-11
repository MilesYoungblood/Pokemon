//
// Created by Miles Youngblood on 12/5/2023.
//

#pragma once

#include "../../BattleItem.h"

struct XSpDefense : public BattleItem {
    explicit XSpDefense(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] Pokemon::Stat getStat() const override;
};
