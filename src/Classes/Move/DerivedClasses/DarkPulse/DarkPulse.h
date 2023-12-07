//
// Created by Miles on 10/6/2023.
//

#pragma once

#include "../../Move.h"

class DarkPulse : public Move {
private:
    const static int MAX_PP = 24;

public:
    DarkPulse();

    void action(Pokemon &attacker, Pokemon &defender, bool &skip) override;

    [[nodiscard]] std::queue<std::string> actionMessage(const Pokemon &attacker, const Pokemon &defender,
                                                         bool skip) const override;

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;
};

namespace {
    inline AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::DARK_PULSE,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<DarkPulse>(); }));
    });
}
