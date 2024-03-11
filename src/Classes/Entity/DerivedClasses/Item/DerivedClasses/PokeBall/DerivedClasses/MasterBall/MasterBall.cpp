//
// Created by Miles Youngblood on 12/6/2023.
//

#include "MasterBall.h"

MasterBall::MasterBall(int n) : PokeBall(n) {}

MasterBall::MasterBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string MasterBall::getName() const {
    return "Master Ball";
}

std::string MasterBall::getEffect() const {
    return "The best Ball with the ultimate level of performance. It will catch any wild Pokemon without fail.";
}

double MasterBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) const {
    return 255.0;
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(pokeBallMutex);
        pokeBalls["Master Ball"] = [](int n) -> std::unique_ptr<PokeBall> { return std::make_unique<MasterBall>(n); };
    });
}
