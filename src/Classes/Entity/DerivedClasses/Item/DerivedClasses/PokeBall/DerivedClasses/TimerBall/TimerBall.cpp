//
// Created by Miles Youngblood on 12/6/2023.
//

#include "TimerBall.h"

TimerBall::TimerBall(int n) : PokeBall(n) {}

TimerBall::TimerBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string TimerBall::getName() const {
    return "Timer Ball";
}

std::string TimerBall::getEffect() const {
    return "A somewhat different Ball that becomes progressively better the more turns there are in a battle.";
}

double TimerBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int turn, bool  /*isCave*/) const {
    return std::min(1 + turn * 1229 / 4069.0, 4.0);
}

namespace {
    std::jthread init([] -> void {
        const std::scoped_lock<std::mutex> scoped_lock(pokeBallMutex);
        pokeBalls["Timer Ball"] = [](int n) -> std::unique_ptr<PokeBall> { return std::make_unique<TimerBall>(n); };
    });
}
