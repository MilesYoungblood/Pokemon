//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../BattleItem.h"

struct XSpeed : public BattleItem {
    explicit XSpeed(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] Pokemon::Stat getStat() const override;

    [[nodiscard]] BattleItem::Id getId() const override;
};
