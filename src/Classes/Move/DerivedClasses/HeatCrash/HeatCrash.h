//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../../Move.h"

class HeatCrash : public Move {
private:
    static const int MAX_PP{ 16 };

public:
    HeatCrash();

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};
