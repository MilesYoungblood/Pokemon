//
// Created by Miles Youngblood on 12/6/2023.
//

#include "PremierBall.h"

PremierBall::PremierBall(int n) : PokeBall(n) {}

PremierBall::PremierBall(int n, int x, int y) : PokeBall(n, x, y) {}

std::string PremierBall::getName() const {
    return "Premier Ball";
}

std::string PremierBall::getEffect() const {
    return "A somewhat rare Poke Ball that has been specially made to commemorate an event of some sort.";
}

PokeBall::Id PremierBall::getId() const {
    return PokeBall::Id::PREMIER_BALL;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokeBallMutex);
        pokeBalls.insert(std::make_pair(PokeBall::Id::PREMIER_BALL, [](int n) -> std::unique_ptr<PokeBall> {
            return std::make_unique<PremierBall>(n);
        }));
    });
}
