//
// Created by Miles Youngblood on 12/6/2023.
//

#include "GreatBall.h"

GreatBall::GreatBall(int n) : PokeBall(n) {}

GreatBall::GreatBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string GreatBall::getName() const {
    return "Great Ball";
}

std::string GreatBall::getEffect() const {
    return "A good, high-performance Ball that provides a higher Pokemon catch rate than a standard Poke Ball.";
}

double GreatBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 1.5;
}

PokeBall::Id GreatBall::getId() const {
    return PokeBall::Id::GREAT_BALL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::GREAT_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<GreatBall>(n);
        }));
    });
}
