//
// Created by Miles Youngblood on 12/6/2023.
//

#include "GreatBall.h"

GreatBall::GreatBall(const int n) : PokeBall("Great Ball", n) {}

GreatBall::GreatBall(const int n, const int x, const int y) : PokeBall("Great Ball", n, x, y) {}

std::string GreatBall::getEffect() const {
    return "A good, high-performance Ball that provides a higher Pokemon catch rate than a standard Poke Ball.";
}

double GreatBall::getCatchRate(const Pokemon & /*pokemon*/, const std::size_t  /*turn*/, const bool  /*isCave*/) const {
    return 1.5;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Great Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<GreatBall>(n); };
    });
}
