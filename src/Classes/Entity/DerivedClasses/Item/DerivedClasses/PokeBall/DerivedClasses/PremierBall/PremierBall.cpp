//
// Created by Miles Youngblood on 12/6/2023.
//

#include "PremierBall.h"

PremierBall::PremierBall(const int n) : PokeBall(n) {}

PremierBall::PremierBall(const int n, const int x, const int y) : PokeBall(n, x, y) {}

std::string PremierBall::getName() const {
    return "Premier Ball";
}

std::string PremierBall::getEffect() const {
    return "A somewhat rare Poke Ball that has been specially made to commemorate an event of some sort.";
}

namespace {
    [[maybe_unused]] std::jthread init([] -> void {
        const std::scoped_lock scopedLock(itemMutex);
        itemMap["Premier Ball"] = [](int n) -> std::unique_ptr<Item> { return std::make_unique<PremierBall>(n); };
    });
}
