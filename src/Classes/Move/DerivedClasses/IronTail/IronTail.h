//
// Created by Miles Youngblood on 6/15/2023.
//

#pragma once

#include "../../Move.h"

class IronTail final : public Move {
public:
    IronTail();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::vector<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                          bool skip) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] int getAccuracy() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Category getCategory() const override;

private:
    static constexpr int max_pp{ 24 };
    bool loweredFlag{ false };
};
