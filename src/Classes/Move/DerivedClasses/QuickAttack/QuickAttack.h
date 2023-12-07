//
// Created by Miles Youngblood on 10/24/2023.
//

#pragma once

#include "../../Move.h"

class QuickAttack : public Move {
private:
    static const int MAX_PP{ 48 };

public:
    QuickAttack();

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] const char *getDescription() const override;

    [[nodiscard]] int getPower() const override;

    [[nodiscard]] Type getType() const override;

    [[nodiscard]] Move::Category getCategory() const override;

    [[nodiscard]] Move::Id getId() const override;

    [[nodiscard]] bool isPriority() const override {
        return true;
    }
};

namespace {
    inline AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(moveMutex);
        moveMap.insert(std::make_pair(Move::Id::IRON_TAIL,
                                      [] -> std::unique_ptr<Move> { return std::make_unique<QuickAttack>(); }));
    });
}
