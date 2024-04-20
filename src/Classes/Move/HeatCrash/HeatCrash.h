//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../Move.h"

class HeatCrash final : public Move {
public:
    HeatCrash();

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Category getCategory() const override;

private:
    static constexpr int max_pp{ 16 };
};
