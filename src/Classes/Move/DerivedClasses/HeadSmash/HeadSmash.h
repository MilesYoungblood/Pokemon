//
// Created by Miles Youngblood on 3/4/2024.
//

#pragma once

#include "../../Move.h"

class HeadSmash : public Move {
private:
    static const int MAX_PP{ 8 };

public:
    HeadSmash();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                        bool skipTurn) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;

    [[nodiscard]] int getAccuracy() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};
