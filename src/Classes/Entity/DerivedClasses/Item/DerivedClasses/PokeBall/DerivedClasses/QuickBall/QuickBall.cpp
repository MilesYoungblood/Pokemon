//
// Created by Miles Youngblood on 12/6/2023.
//

#include "QuickBall.h"

QuickBall::QuickBall(const int n) : PokeBall(n) {}

QuickBall::QuickBall(const int n, const int x, const int y) : PokeBall(n, x, y) {}

std::string QuickBall::getName() const {
    return "Quick Ball";
}

std::string QuickBall::getEffect() const {
    return "A somewhat different Poké Ball that provides a better catch rate if it is used at the start of a wild encounter.";
}

double QuickBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, const int turn, bool  /*isCave*/) const {
    return turn > 1 ? 1.0 : 5.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Quick Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<QuickBall>(n); };
    });
}
