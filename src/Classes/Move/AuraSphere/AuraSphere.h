//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

#include "../Move.h"

class AuraSphere final : public Move {
public:
    AuraSphere();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Category getCategory() const override;

private:
    static constexpr int max_pp = 32;
};
