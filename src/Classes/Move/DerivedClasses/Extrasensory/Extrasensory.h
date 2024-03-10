//
// Created by Miles on 10/6/2023.
//

#pragma once

#include "../../Move.h"

class Extrasensory : public Move {
private:
    static const int MAX_PP = 32;       // FIXME likely incorrect

public:
    Extrasensory();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::vector<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                          bool skip) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;
};
