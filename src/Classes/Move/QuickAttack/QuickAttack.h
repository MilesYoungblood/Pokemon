//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

#include "../Move.h"

class QuickAttack final : public Move {
public:
    QuickAttack();

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Category getCategory() const override;

    [[nodiscard]] bool isPriority() const override;

private:
    static constexpr int max_pp{ 48 };
};
