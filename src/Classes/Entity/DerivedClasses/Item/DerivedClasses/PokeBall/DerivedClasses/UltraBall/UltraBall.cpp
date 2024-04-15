//
// Created by Miles Youngblood on 12/6/2023.
//

#include "UltraBall.h"

UltraBall::UltraBall(const int n) : PokeBall(n) {}

UltraBall::UltraBall(const int n, const int x, const int y) : PokeBall(n, x, y) {}

std::string UltraBall::getName() const {
    return "Ultra Ball";
}

std::string UltraBall::getEffect() const {
    return "An ultra-performance Ball that provides a higher Pokemon catch rate than a Great Ball.";
}

double UltraBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 2.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Ultra Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<UltraBall>(n); };
    });
}
