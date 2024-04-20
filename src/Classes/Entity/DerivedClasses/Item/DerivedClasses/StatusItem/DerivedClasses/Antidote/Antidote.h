//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../StatusItem.h"

struct Antidote final : StatusItem {
    explicit Antidote(int n);

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] StatusCondition getStatus() const override;
};
