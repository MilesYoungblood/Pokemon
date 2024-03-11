//
// Created by Miles Youngblood on 12/6/2023.
//

#include "DuskBall.h"

DuskBall::DuskBall(int n) : PokeBall(n) {}

DuskBall::DuskBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string DuskBall::getName() const {
    return "Dusk Ball";
}

std::string DuskBall::getEffect() const {
    return "A somewhat different Poke Ball that makes it easier to catch wild Pokemon at night or in dark places like caves.";
}

double DuskBall::getCatchRate(const Pokemon & /*pokemon*/, Time time, int  /*turn*/, bool isCave) const {
    return time == Time::NIGHT or isCave ? 3.5 : 1.0;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(itemMutex);
        itemMap["Dusk Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<DuskBall>(n); };
    });
}
