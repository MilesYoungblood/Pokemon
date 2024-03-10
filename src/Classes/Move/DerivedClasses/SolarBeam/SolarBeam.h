//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

#include "../../Move.h"

//TODO solar beam action
class SolarBeam : public Move {
private:
    static const int MAX_PP{ 16 };

public:
    SolarBeam();

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getDescription() const override;

    [[nodiscard]] int getPower(const Pokemon &attacker, const Pokemon &defender) const override;;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;
};
