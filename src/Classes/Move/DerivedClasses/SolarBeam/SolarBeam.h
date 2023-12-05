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

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};

namespace {
    inline AutoThread init([] -> void {
        moveMap.insert(std::make_pair(Move::Id::SOLAR_BEAM,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<SolarBeam>(); }));
    });
}
