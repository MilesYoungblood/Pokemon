//
// Created by Miles Youngblood on 12/6/2023.
//

#include "QuickBall.h"

QuickBall::QuickBall(const int n) : PokeBall("Quick Ball", n) {}

QuickBall::QuickBall(const int n, const int x, const int y) : PokeBall("Quick Ball", n, x, y) {}

std::string QuickBall::getEffect() const {
    return "A somewhat different Poké Ball that provides a better catch rate if it is used at the start of a wild encounter.";
}

double QuickBall::getCatchRate(const Pokemon & /*pokemon*/, const std::size_t turn, const bool  /*isCave*/) const {
    return turn > 1 ? 1.0 : 5.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Quick Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<QuickBall>(n); };
    });
}
