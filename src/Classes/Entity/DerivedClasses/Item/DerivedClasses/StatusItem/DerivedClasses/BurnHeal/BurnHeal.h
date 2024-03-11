//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../StatusItem.h"

struct BurnHeal : public StatusItem {
    explicit BurnHeal(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] StatusCondition getStatus() const override;
};
