//
// Created by Miles Youngblood on 12/6/2023.
//

#include "QuickBall.h"

QuickBall::QuickBall(int n) : PokeBall(n) {}

QuickBall::QuickBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string QuickBall::getName() const {
    return "Quick Ball";
}

std::string QuickBall::getEffect() const {
    return "A somewhat different Poké Ball that provides a better catch rate if it is used at the start of a wild encounter.";
}

double QuickBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int turn, bool  /*isCave*/) const {
    return turn > 1 ? 1.0 : 5.0;
}

PokeBall::Id QuickBall::getId() const {
    return PokeBall::Id::QUICK_BALL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::QUICK_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<QuickBall>(n);
        }));
    });
}
