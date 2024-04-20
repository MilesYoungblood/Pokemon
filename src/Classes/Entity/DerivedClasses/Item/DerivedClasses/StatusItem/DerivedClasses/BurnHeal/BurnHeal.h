//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../StatusItem.h"

struct BurnHeal final : StatusItem {
    explicit BurnHeal(int n);

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] StatusCondition getStatus() const override;
};
