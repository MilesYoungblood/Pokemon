//
// Created by Miles Youngblood on 12/6/2023.
//

#include "UltraBall.h"

UltraBall::UltraBall(int quantity) : PokeBall(quantity) {}

std::string UltraBall::getName() const {
    return "Ultra Ball";
}

std::string UltraBall::getEffect() const {
    return "An ultra-performance Ball that provides a higher Pokemon catch rate than a Great Ball.";
}

double UltraBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 2.0;
}

PokeBall::Id UltraBall::getId() const {
    return PokeBall::Id::ULTRA_BALL;
}

namespace {
    AutoThread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::ULTRA_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<UltraBall>(n);
        }));
    });
}
