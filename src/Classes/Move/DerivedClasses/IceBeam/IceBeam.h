//
// Created by Miles Youngblood on 6/14/2023.
//

#pragma once

#include "../../Move.h"

class IceBeam : public Move {
private:
    static const int MAX_PP{ 16 };
    bool freezeFlag{ false };

public:
    IceBeam();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                         bool skipTurn) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};

namespace {
    inline AutoThread init([] -> void {
        moveMap.insert(std::make_pair(Move::Id::ICE_BEAM,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<IceBeam>(); }));
    });
}
