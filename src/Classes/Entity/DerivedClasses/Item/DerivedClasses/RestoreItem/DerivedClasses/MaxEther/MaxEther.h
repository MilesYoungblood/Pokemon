//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../RestoreItem.h"

struct MaxEther : public RestoreItem {
    explicit MaxEther(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] int getAmount() const override;

    [[nodiscard]] bool isHp() const override;
};
