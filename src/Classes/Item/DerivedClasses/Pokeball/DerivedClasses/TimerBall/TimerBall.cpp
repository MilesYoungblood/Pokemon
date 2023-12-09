//
// Created by Miles Youngblood on 12/6/2023.
//

#include "TimerBall.h"

TimerBall::TimerBall(int quantity) : PokeBall(quantity) {}

std::string TimerBall::getName() const {
    return "Timer Ball";
}

std::string TimerBall::getEffect() const {
    return "A somewhat different Ball that becomes progressively better the more turns there are in a battle.";
}

double TimerBall::getCatchRate(const Pokemon & /*pokemon*/, Time  /*time*/, int turn, bool  /*isCave*/) const {
    return std::min(1 + turn * 1229 / 4069.0, 4.0);
}

PokeBall::Id TimerBall::getId() const {
    return PokeBall::Id::TIMER_BALL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::TIMER_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<TimerBall>(n);
        }));
    });
}
