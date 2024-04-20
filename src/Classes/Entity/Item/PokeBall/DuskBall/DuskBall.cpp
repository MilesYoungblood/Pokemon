//
// Created by Miles Youngblood on 12/6/2023.
//

#include "DuskBall.h"

DuskBall::DuskBall(const int n) : PokeBall("Dusk Ball", n) {}

DuskBall::DuskBall(const int n, const int x, const int y) : PokeBall("Dusk Ball", n, x, y) {}

std::string DuskBall::getEffect() const {
    return "A somewhat different Poke Ball that makes it easier to catch wild Pokemon at night or in dark places like caves.";
}

double DuskBall::getCatchRate(const Pokemon & /*pokemon*/, const std::size_t  /*turn*/, const bool isCave) const {
    return isCave ? 3.5 : 1.0;
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Dusk Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<DuskBall>(n); };
    });
}
