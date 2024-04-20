//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../Move.h"

class HeadSmash final : public Move {
public:
    HeadSmash();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::vector<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                          bool skipTurn) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] int getAccuracy() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Category getCategory() const override;

private:
    static constexpr int max_pp{ 8 };
};
