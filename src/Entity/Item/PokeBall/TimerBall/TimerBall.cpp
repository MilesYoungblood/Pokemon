//
// Created by Miles Youngblood on 12/6/2023.
//

#include "TimerBall.h"

TimerBall::TimerBall(const int n) : PokeBall("Timer Ball", n) {}

TimerBall::TimerBall(const int n, const int x, const int y) : PokeBall("Timer Ball", n, x, y) {}

std::string TimerBall::getEffect() const {
    return "A somewhat different Ball that becomes progressively better the more turns there are in a battle.";
}

double TimerBall::getCatchRate(const Pokemon & /*pokemon*/, const std::size_t turn, const bool  /*isCave*/) const {
    return std::min(1 + static_cast<double>(turn) * 1229 / 4069.0, 4.0);
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Timer Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<TimerBall>(n); };
    });
}
