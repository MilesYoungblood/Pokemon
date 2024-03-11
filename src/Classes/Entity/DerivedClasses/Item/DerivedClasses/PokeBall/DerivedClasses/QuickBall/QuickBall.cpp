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

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Quick Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<QuickBall>(n); };
    });
}
